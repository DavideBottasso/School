#include "Address.hpp"
#include <string.h>
#include "mylib.h"

#define PORT_MYSELF 8080
#define MAX_MSG 4096

void errore(int n, char*s){
	printf("Errore%d %s\n", errno, strerror(errno));
	printf("Durante %s.Esco con %d\n", s, n);
	exit(n);
}

int main(int argc, char const *argv[]){

	
	int socketId;
	printf("Apertura del socket\n");
	socketId = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(socketId<0) errore(-1, "socket()");
	printf("Ok\n");

	Address myself(IP_DHCP, PORT_MYSELF);

	struct sockaddr_in addrMyself = myself.getSockAddr();
	
	printf("Associo IP e porta al socket...\n");
	int ret=bind(socketId, (struct sockaddr*)&addrMyself, (socklen_t)sizeof(struct sockaddr_in));
	if(ret) errore(-2, "bind()");
	printf("Ok\n");

	char buffer[MAX_MSG + 1];
	struct sockaddr_in mittAddr;
	int addrLen(sizeof(struct sockaddr_in));
	recvfrom(socketId, buffer, MAX_MSG, 0, (struct sockaddr*)&mittAddr, (socklen_t*)&addrLen);
	if (ret<=0)errore(-3, "recvfrom()");
	buffer[ret]='\0';
	Address mittente(mittAddr);
	char*mittstr = mittente.toString();
	printf("%s:'%s'\n",mittstr, buffer);
	free(mittstr);

	char msg[]="Ciao, sono il tuo server";
	sendto(socketId, msg, lenStr(msg)+1, 0, (struct sockaddr*)&mittAddr, (socklen_t)sizeof(struct sockaddr_in),);
	if (ret == lenStr(msg)+1)errore(-4,"sendto()");

	close(socketId);

	return 0;
}
apre socket non fa bind invia server alla risposta e chiude