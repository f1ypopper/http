#ifndef REQUESTS_H
#define REQUESTS_H
#include "HttpResponse.h"
#include "HttpRequest.h"
#include <string>
#include <map>
enum Method{
	GET,
	POST
};

struct Url{
	std::string scheme;
	std::string host;
	std::string path;
};

HttpResponse request(Method type, std::string url,
			std::map<std::string, std::string>params,
			std::map<std::string, std::string>headers,
			std::string data);

HttpRequest create_request(Method type, 
						std::string url,
						std::map<std::string, std::string> params,
						std::map<std::string, std::string>headers,
						std::string data);

std::string create_query_string(std::map<std::string, std::string> params);
std::string url_encode(std::string str);
Url url_split(std::string url);

#endif
