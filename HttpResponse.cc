#include "HttpResponse.h"
#include <string>
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
		std::cout << section << std::endl;
		out.push_back(section);
	}
	return out;
}
std::vector<std::string> parse_status_line(std::string status_line){
	std::vector<std::string> parsed_line;
	std::stringstream status_line_stream(status_line);
	std::string section;
	while (std::getline(status_line_stream, section, ' '))
	{
		parsed_line.push_back(section);
	}
	return parsed_line;
}

std::map<std::string, std::string> parse_headers(std::string source){
	std::map<std::string, std::string> headers;
	std::stringstream header_source_stream(source);
	std::string raw_header;
	while(std::getline(header_source_stream, raw_header, '\r')){
		int colon_index = raw_header.find(":");
		std::string key = raw_header.substr(0, colon_index);
		std::cout << key << std::endl;
		std::string value = raw_header.substr(colon_index+1);
		std::cout << value << std::endl;
		headers[key] = value;
	}
	return headers;
}

HttpResponse parse_http_response(std::string source){
	std::stringstream source_stream(source);
	std::vector<std::string> split_response;
	std::string section;
	while (std::getline(source_stream, section, '\r'))
	{
		split_response.push_back(section);
	}

	std::string status_line = split_response.at(0);
	std::string headers = split_response.at(1);
	std::string body = split_response.at(2);

	std::vector<std::string> parsed_status_line = parse_status_line(status_line);
	std::map<std::string, std::string> parsed_headers_map = parse_headers(headers);		

	return HttpResponse{.status_code=parsed_status_line.at(1), .status_message=parsed_status_line.at(2), .data=body, .headers=parsed_headers_map};
}

