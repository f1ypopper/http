#include "HttpRequest.h"
#include "requests.h"
#include <map>
#include <iostream>

int main(){

	std::map<std::string, std::string> headers;
	headers["Accept-Language"] = "en";
	std::map<std::string, std::string> params;	
	params["hello"] = "hola";
	params["bye"] = "adios me";
	HttpRequest req = create_request(Method::GET, "http://www.google.com/hi",params,headers,"");
	req.construct();
	std::cout << req.constructed_message() << std::endl;
	return 0;
}
