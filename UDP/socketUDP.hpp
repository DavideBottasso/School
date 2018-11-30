#include "address.hpp"
#include <unistd.h>

#include <errno.h>

#define MAX_MESSAGE 4096
#define DEFAULT_PORT 8080

#define IMAGE_FOLDER "image/"
#define IMAGE_RECEIVED_NAME "tmp.cr2"

#ifndef __SOCKETUDP_HPP
#define __SOCKETUDP_HPP

class SocketUDP {
private:	int	socketId;
public:		SocketUDP(int, bool);

		bool	invia(char*, Address);
		char*	ricevi(Address*);

		bool	invia_raw(char*, Address);
		FILE*	ricevi_raw(Address* mitt);

		~SocketUDP();
};

/* Valori di default del costruttore in C++ */
/* CTRL + ALT + Fn */

SocketUDP::SocketUDP(int port = DEFAULT_PORT, bool loopback = false) {
	char* ip;

	this->socketId = socket(AF_INET, SOCK_DGRAM, 0);
	if (loopback)
		ip = strdup(IP_LO);
	else
		ip = strdup(IP_DHCP);

	Address address (strdup(ip), port);
	struct sockaddr_in socketAddr = address.getBinary();

	if (loopback)
		bind(this->socketId, (struct sockaddr*) &socketAddr, sizeof(struct sockaddr_in));
}

bool SocketUDP::invia(char* msg, Address dest) {
	struct sockaddr_in sockDest = dest.getBinary();
	char messaggio[MAX_MESSAGE];
	strcpy(messaggio, strdup(msg));

	int ret = sendto(this->socketId, messaggio, strlen(messaggio) + 1, 0, (struct sockaddr*) &sockDest, (socklen_t) sizeof(struct sockaddr_in));
	return (ret < 0);
}

char* SocketUDP::ricevi(Address* mitt) {
	char buffer[MAX_MESSAGE + 1];
	struct sockaddr_in sockMitt;
	socklen_t len = sizeof(struct sockaddr_in);	/* Altrimenti si incorre in un errore (Bad Address) */

	int length = recvfrom(this->socketId, buffer, MAX_MESSAGE, 0, (struct sockaddr*) &sockMitt, &len);
	mitt->setBinary(sockMitt);

	buffer[length] = '\0';

	return strdup(buffer);
}

bool invia_raw::invia(char* byte, Address dest){

}

FILE*ricevi_raw::ricevi(Address* mitt){

}

SocketUDP::~SocketUDP() {
	close(socketId);
	printf("Distruzione SocketUDP\n");
}

#endif // __SOCKETUDP_HPP
