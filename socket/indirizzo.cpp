#include "Address.hpp"
#include <string.h>
#include "mylib.h"

#define PORT_MYSELF 1026
#define MAX_MSG 4096

int main(int argc, char* argv[]){
	
	int socketid;
	printf("Apertura del socket...");
	socketid = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketid <0){
		errore(-1, "socket()");
	}
	printf("Ok\n");
	
	Address myself(IP_DHCP, PORT_MYSELF);
	struct sockaddr_in addrMyself = myself.getBinary();
	print("Associo port e ip...");
	int ret = bind(socketid, 
		(struct sockaddr*) &addrMyself,
		(socklen_t) sizeof(struct sockaddr_in));
	if(ret) errore(-2, "bind()");
	printf("Ok\n");
	
	char buffer[MAX_MSG +1]; //allocazione di 4k byte
	struct sockaddr_in mittAddr;
	int addrLen = sizeof(struct sockaddr_in);
	ret = recvfrom(socketid, buffer, MAX_MSG, 0,
			(struct sockaddr)&mittAddr,
			(socklen_t*)&addrLen);
	if(ret <= 0) errore(-3, "recv()");
	Address mittente(mittAddr);
	char* mittStr = mittente.toString();
	buffer[ret]='\0';
	printf("%s: '%s'\n", mittStr, buffer);
	free(mittStr);
	
	char msg[] = "Ciao sono il tuo server";
	ret = sendto(socketid, msg, lenstr(msg)+1, 0,
			(struct sockaddr)&mittAddr, 
			(socklen_t)sizeof(struct sockaddr_in) );
	if(ret != lenstr(msg) +1) errore(-4, "sendto()");


	close(socketid);




	return 0;
}