#ifndef __ADDRESS_HPP // dunder
#define __ADDRESS_HPP

#define IP_DHCP "0.0.0.0"
#define LOOPBACK "127.0.0.1"
#define PORT_ZERO 0
#define LEN_ADDRESS_STR 25

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //?
#include <arpa/inet.h>
#include <cstdlib>

/*
Sockaddr
*/

class Address {
	private:char* 	ip;
		int 	port;
		static pthread_mutex mutex;
	public: //(...)
		void setSockaddr(struct sockaddr_in sockaddr);
		//(...)
			
	public: Address(char*, int);
			Address();
			Address(const Address&);
			Address(const struct sockaddr_in&);
			
			char* 				getIp();
			int 				getPort();
			struct sockaddr_in	getBinary();
			void 				setIp(char*);
			void 				setPort(int);
			void 				setBinary(struct sockaddr_in);
			
			char* 	toString();
			
			~Address();
			
};

pthread_mutex Address::mutex=PTHREAD_MUTEX_INITIALIZER;

void Address::setSockaddr(struct sockaddr_in a){
	if(this->ip) free(this->ip);
	this->port=ntohs(a.s.m_port);
	/*
	rendo inet thread safe
	*/
	pthread_mutex_lock(&mutex);
	this->ip=strdup(inet_ntoa(a.sinaddr));
	pthread_mutex_unlock(&mutex)
}

/*
COSTRUTTORI
*/

Address::Address(char* ip, int port) {
	this->ip = dupstr(ip);
	this->port = port;
	
	printf("Address@%p\n", this);
}

Address::Address() {
	this->ip = dupstr(IP_DHCP);
	this->port = PORT_ZERO;
	
	printf("Address@%p\n", this);
}

Address::Address(const Address& a) { //Address&: passaggio per copia di Address (sintassi per copia, a basso livello passato per referenza)
	this->ip = a.getIp();
	this->port = a.getPort();
	
	printf("Address@%p\n", this);
}

Address::Address(const sockaddr_in& a){ //Check class sockaddr
	this->ip = dupstr(inet_ntoa(a.sin_addr));
	this->port = ntohs(a.sin_port);
}


/*
GETTER
*/

char* 	Address::getIp() {
	return dupstr(this->ip);
}
int 	Address::getPort() {
	return (this-> port);
}

/*
Crea una struct sockaddr_in utilizzando come proprietà le proprietà
di questa istanza di Address(this).

Returns : struct sockaddr_in
*/
sockaddr_in Address::getBinary(){
	struct sockaddr_in ret;
	
	ret = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
	ret.sin_family = AF_INET;
	inet_aton(this->ip, ret.sin_addr);
	ret.sin_port = htons(this->port);
	for(int i=0; i < 8; i++){
		ret.sin_zero[i] = 0;
	}

	return ret;
}

/*
SETTER
*/

void 	Address::setIp(char* ip) {
	free(this->ip);
	this->ip = dupstr(ip);
}
void 	Address::setPort(int port) {
	this->port = port;
}

/*
Imposta le proprietà di questa istanza di Address(this)
in base alle proprietà della struct sockaddr passata come parametro.
*/
void Address::setBinary(struct sockaddr a){

	free(this->ip);
	this->ip = dupstr(inet_ntoad(a.sin_addr));
	this->port = ntohs(a.sin_port);
}


/*
TO STRING

Crea una stringa contenente l'indirizzo ip e la porta
di questa istanza(this).

Returns : string "[<ip_address>:<port>]"
*/		
char* 	Address::toString() {
	char temp[LEN_ADDRESS_STR];
	
	sprintf(temp, "[%s:%d]", this->ip, this->port);
	return strdup(temp);
	
}

/*DISTRUTTORE*/			
Address::~Address() {
	char* temp;
	printf("Distruttore di %s\n", temp = this->toString());
	free(temp);
	free(this->ip);
	printf("Distruggo Address@%p\n", this);
}


#endif //__ADDRESS_HPP


