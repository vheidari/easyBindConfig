#include <iostream>
#include <arpa/inet.h>

using namespace std;
class Validate {
	
public:
		
	// validate ip address input by user
	// help link :
	//	-- http://www.zedwood.com/article/cpp-is-valid-ip-address-ipv4-ipv6
	bool validateIpV4Address(string ipAddress)
	{
		struct sockaddr_in sa;
		return inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr))!=0;
	}	
};