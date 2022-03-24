#include "requests.h"
#include "HttpRequest.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <map>
#include <string>
#include <cstring>

void request(Method type, std::string url,
					std::map<std::string, std::string>params,
					std::map<std::string, std::string>headers,
					std::string data)
{
	HttpRequest req = create_request(type, url, params, headers, data);
	Url parsed_url = url_split(url);
	req.construct();

	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET_ADDRSTRLEN];
	std::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
    if ((status = getaddrinfo(parsed_url.host.data(), "http", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }
	for(p = res; p != NULL ; p = p->ai_next){
		void *addr;
		char *ipver;

		if(p->ai_family == AF_INET){
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
			inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
			break;
		}
	}

	int sockfd;
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	int connected = connect(sockfd, res->ai_addr, res->ai_addrlen);
	int bytes_sent = send(sockfd, req.constructed_message().data(), req.constructed_message().length(), 0);
	int BUFFER_LEN = 1024;
	char buffer[BUFFER_LEN];
	std::string recvd_data;
	while(true){
		int recv_len = recv(sockfd, buffer, BUFFER_LEN, 0);
		if(recv_len == 0)
			break;
		recvd_data.append(std::string(buffer,BUFFER_LEN));
	}
	std::cout << recvd_data << std::endl;
}

HttpRequest create_request(Method type, 
						std::string url,
						std::map<std::string, std::string> params,
						std::map<std::string, std::string>headers,
						std::string data)
{
	HttpRequest req("GET");
	if(type == Method::GET)
		req.method = "GET";
	if(type == Method::POST)
		req.method = "POST";


	Url parsed_url = url_split(url);
	std::string query_string = create_query_string(params);
	req.add_url(parsed_url.path+query_string);
	req.add_headers(headers);
	req.add_header("Host", parsed_url.host);
	if(!data.empty())
		req.add_body(data);

	return req;	
}

std::string create_query_string(std::map<std::string, std::string> params){
	std::string query;
	if(params.empty()){
		return "";
	}
	query.append("?");
	for(auto const& params : params){
		std::string encoded_key = url_encode(params.first);
		std::string encoded_value = url_encode(params.second);
		query.append(encoded_key+"="+encoded_value+"&");
	}
	return query.substr(0,query.length()-1);//return the string without the last ampersand
}

//Url Encoding function can be improved
std::string url_encode(std::string str){
	std::string encoded;
	for(int i=0; i < str.length(); i++){
		if(str.at(i) == ' ')
			encoded.append("%20");
		else if(str.at(i) == '!')
			encoded.append("%21");
		else if(str.at(i) == '#')
			encoded.append("%23");
		else if(str.at(i) == '$')
			encoded.append("%24");
		else if(str.at(i) == '%')
			encoded.append("%25");
		else if(str.at(i) == '&')
			encoded.append("%26");
		else if(str.at(i) == '\'')
			encoded.append("%27");
		else if(str.at(i) == '(')
			encoded.append("%28");
		else if(str.at(i) == ')')
			encoded.append("%29");
		else if(str.at(i) == '*')
			encoded.append("%2A");
		else if(str.at(i) == '+')
			encoded.append("%2B");
		else if(str.at(i) == ',')
			encoded.append("%2C");
		else if(str.at(i) == '/')
			encoded.append("%2F");
		else if(str.at(i) == ':')
			encoded.append("%3A");
		else if(str.at(i) == ';')
			encoded.append("%3B");
		else if(str.at(i) == '=')
			encoded.append("%3D");
		else if(str.at(i) == '?')
			encoded.append("%3F");
		else if(str.at(i) == '@')
			encoded.append("%40");
		else if(str.at(i) == '[')
			encoded.append("%5B");
		else if(str.at(i) == ']')
			encoded.append("%5D");
		else
			encoded+=str.at(i);	
	}
	return encoded;
}

Url url_split(std::string url){
	int scheme_colon_index = url.find(':');
	std::string scheme = url.substr(0,scheme_colon_index);
	int host_start_index = scheme_colon_index+3; //Consume the '//'
	int slash_index = url.substr(host_start_index).find('/');			
	std::string host = url.substr(host_start_index, slash_index);
	std::string path = url.substr(host_start_index).substr(slash_index);
	return Url{.scheme=scheme, .host=host, .path=path};
}