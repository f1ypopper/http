#ifndef HTTP_RESP_H
#define HTTP_RESP_H
#include <string>
#include <map>
#include <vector>
class HttpResponse{
	public:
		std::string status_code;
		std::string status_message;
		std::string data;
		std::map<std::string, std::string> headers;	
};

HttpResponse parse_http_response(std::string response);
std::vector<std::string> split(std::string str, std::string delim);
#endif