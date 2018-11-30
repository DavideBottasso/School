 #include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#ifndef __ADDRESS_HPP
#define __ADDRESS_HPP

#define IP_DHCP "0.0.0.0"
#define PORT_ZERO 0

#define IP_LOOPBACK "127.0.0.1"
#define LEN_ADDRESS__STR 23

class Address{
	private:char* ip;
			int   port
	public: Address(char*, int);
	Address();
	Address(const Address&);
	Address(const sockaddr&);
	
	char* 				getIp();
	int 				getPort();
	struct sockaddr_in 	getSockAddr();
	void 				setIp(char* ip);
	void 				setPort(int);
	
	char* toString();
	
	~Address();
};

Address::Address(char* ip, int port){
	this->ip = dupstr(ip);
	this->port = port;
	
	printf("Creato address @%p\n", this);
}
Address::Address(){
	this->ip = dupstr(IP_DHCP);
	this->port = PORT_ZERO;
}

//Il contenuto di address non può essere cambiato
Address::Address(const Address& address){
	this->ip = address.getIp();
	this->port = address.getPort();

	printf("Address%p\n", this);
}

Address::Address(const sockaddr& a){
	this->ip = dupstr(inet_ntoa(a.sin_addr));
	this->port = ntohs(a.sin_port);
}

char* Address::getIp(){
	return dupstr(this->ip);
}
int Address::getPort(){
	return dupstr(this->port);
}

struct sockaddr_in Address::getSockAddr(){
	struct sockaddr_in ret;

	ret = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	ret.sin_family = AF_INET;
	inet_aton(this->ip, ret.sin_addr);
	ret.sin_port = this->port;
	for(int i=0; i<8; i++){
		ret.sin_zero[i] = 0;
	}
}



void Address::setIp(char* ip){
	free(this->ip);
	this->ip = dupstr( ip);
}
void Address::setPort(int port){
	this->port = port;
}
char* Address::toString(){
	char temp[LEN_ADDRESS__STR];
	
sprintf(temp, "[%s:%d]", this->ip, this->port);
	return dupstr(temp);
}
Address::~Address(){
	free(this->ip);
	printf("Distruggo Address@%p\n", this);
}

#endif // __ADDRESS_HPP