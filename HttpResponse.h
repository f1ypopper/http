#ifndef HTTP_RESP_H
#define HTTP_RESP_H
#include <string>
#include <map>
using namespace std;

class HttpResponse{
	public:
		int status_code;
		string status_text;
		string content;
		map<string, string> headers;	
};

HttpResponse parse_http_response(string response){

}
#endif