#include "HttpResponse.h"
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>


std::vector<std::string> split(std::string str, std::string delim){
	int index = -delim.length();	
	std::string s = str;
	std::vector<std::string> out;
	while(true){
		index = s.find(delim);
		if(index == -1){
			out.push_back(s);
			break;
		}
		std::string section = s.substr(0,index);
		s = s.substr(index+delim.length());
		out.push_back(section);
	}
	return out;
}

std::string trim(std::string str){
	int start_offset;
	int end_offset;
	for(start_offset = 0; start_offset <= str.length(); start_offset++){
		if(str.at(start_offset) != ' '){
			break;
		}
	}
	for(end_offset = str.length()-1; end_offset >= 0; end_offset--){
		if(str.at(end_offset) != ' '){
			break;
		}
	}
	return str.substr(start_offset,end_offset+1);
}

std::vector<std::string> parse_status_line(std::string status_line){
	std::vector<std::string> parsed_line;
	for (auto &section: split(status_line, " "))
	{
		parsed_line.push_back(section);
	}
	return parsed_line;
}

std::map<std::string, std::string> parse_headers(std::vector<std::string> source){
	std::map<std::string, std::string> headers;
	for(auto &raw_header: source){
		int colon_index = raw_header.find(":");
		std::string key = raw_header.substr(0, colon_index);
		std::string value = raw_header.substr(colon_index+1);
		headers[trim(key)] = trim(value);
	}
	return headers;
}

HttpResponse parse_http_response(std::string source){
	std::vector<std::string> split_response;
	int header_end_index=0;
	int count=0;
	for (auto &section: split(source,"\r\n"))
	{
		if(section.empty()){
			header_end_index=count;
		}
		split_response.push_back(section);
		count+=1;
	}

	std::string status_line = split_response.at(0);

	std::vector<std::string> headers = {split_response.begin()+1, split_response.begin()+header_end_index};
	std::string body = split_response.at(split_response.size()-1);
	std::vector<std::string> parsed_status_line = parse_status_line(status_line);
	std::map<std::string, std::string> parsed_headers_map = parse_headers(headers);		

	return HttpResponse{.status_code=parsed_status_line.at(1), .status_message=parsed_status_line.at(2), .data=body, .headers=parsed_headers_map};
}

