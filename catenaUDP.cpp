#include "Address.hpp"
#include <string.h>
#include <unistd.h>

#define MAX_MSG_SIZE 4096

int main(int argc, char* argv[]) {
    
    if(argc!=4){
        printf("USAGE: %s PORT SERVERIP SERVERPORT\n", argv[0]);
        return(-1);
    }
    int my_port = atoi(argv[1]);
    char* server_ip = argv[2];
    int server_port = atoi(argv[3]);
    
    printf("Apro il socket\n");
	int socketId = socket(AF_INET, SOCK_DGRAM, 0);
	
	Address mySelf(IP_DHCP, my_port);
	Address sendTo_(server_ip,server_port);
	struct sockaddr_in addrMySelf = mySelf.getSockaddr_in();
	struct sockaddr_in sentou =sendTo_.getSockaddr_in();
	
	bind(socketId, (struct sockaddr *)&addrMySelf, (socklen_t)sizeof(struct sockaddr_in));	
	
	char buffer[MAX_MSG_SIZE + 1];
	
	struct sockaddr_in addrClient;
	int addrLen = sizeof(struct sockaddr_in);
	
	int ret =recvfrom(socketId, buffer, MAX_MSG_SIZE, 0, (sockaddr *)&addrClient, (socklen_t *)&addrLen);
	
	buffer[ret] = '\0';
	
	Address client(addrClient);
	
	printf("Ho ricevuto il messaggio: %s\n", buffer);
	
	sendto(socketId, buffer, strlen(buffer) + 1, 0, (struct sockaddr *)&sentou, (socklen_t)sizeof(struct sockaddr_in));
	
	close(socketId);
	       
	return 0;
}

