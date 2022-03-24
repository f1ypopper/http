#include "HttpRequest.h"
#include "HttpResponse.h"
#include "requests.h"
#include <map>
#include <iostream>

int main(){

	std::map<std::string, std::string> headers;
	headers["Accept-Language"] = "en";
	headers["Connection"] = "close";
	std::map<std::string, std::string> params;	
	params["hello"] = "hola";
	params["bye"] = "adios me";
	//HttpRequest req = create_request(Method::GET, "http://www.example.com/",params,headers,"");
	//req.construct();
	//request(Method::GET, "http://www.example.com/",params,headers,"");

//	HttpResponse resp = parse_http_response("HTTP/1.1 200 OK\r\nContent-Length: 155\r\n<html>\n<head>");
	//std::cout << resp.status_code << std::endl;
	//std::cout << resp.headers["Content-Length"] << std::endl;
	std::vector<std::string> out = split("hello!!atharva!!guys","!!");
	return 0;
}
