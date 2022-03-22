#include "HttpRequest.h"

HttpRequest::HttpRequest(std::string method){
	std::set<std::string> methods = {"GET", "POST"};
	if(methods.count(method) == 0){
		throw "Invalid Method.";
	}
	HttpRequest::method = method;
	body = "";
}

void HttpRequest::add_header(std::string key, std::string value){
	headers[key] = value;
}

void HttpRequest::add_headers(std::map<std::string, std::string> head){
	headers = head;
}
void HttpRequest::add_body(std::string body){
	HttpRequest::body = body;
}

void HttpRequest::add_url(std::string url){
	HttpRequest::url = url;
}

void HttpRequest::construct(){
	std::string request_line = construct_request_line();
	std::string headers_text = construct_headers();
	message = request_line+headers_text+"\r\n"+body;
}

std::string HttpRequest::construct_headers(){
	std::string header_text;
	for (auto const &header: headers){
		header_text.append(header.first+": "+header.second+"\r\n");
	}
	return header_text;
}

std::string HttpRequest::construct_request_line(){
	std::string request_line;
	request_line = method + " " + url + " " + http_version+"\r\n";
	return request_line;
}

std::string HttpRequest::constructed_message(){
	return message;
}
