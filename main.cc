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
	params["id"] = "30798539";
	HttpResponse resp = request(Method::GET, "http://quietoldslowpeace.neverssl.com/online",params,headers,"");

	std::cout << resp.data << std::endl;
	return 0;
}
