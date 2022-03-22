#ifndef HTTP_REQ_H
#define HTTP_REQ_H
#include <string>
#include <map>
#include <set>
#include <iostream>

class HttpRequest{
	public:
		HttpRequest(std::string method);
		HttpRequest();
		std::string method;
		std::map<std::string, std::string> headers;
		std::string body;	
		std::string message;
		std::string url;
		void add_header(std::string key, std::string value);
		void add_headers(std::map<std::string, std::string> head);
		void construct();
		void add_body(std::string body);
		void add_url(std::string url);
		std::string constructed_message();
	private:
		std::string http_version = "HTTP/1.1";
		std::string construct_request_line();
		std::string construct_headers();
};
#endif