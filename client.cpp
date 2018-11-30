#include "include/Address.hpp"
#include "include/myLib.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_MSG 4096

int main(int argc, char*argv[]){
	char* serverIp;
	int serverPort;
	char* msg;
	int socketid;
	struct sockaddr_in server;
	char buffer[MAX_MSG+1];
	int ret;
	int lenAddr;
	
	if(argc != 4){
		printf("USAGE: %s [SERVER_IP] [SERVER_PORT] [MESSAGE]\n", argv[0]);
		return -1;
	}
	
	serverIp = argv[1];
	serverPort = atoi((char*)atoi(*(argv+2)));
	
	
	
	return 0;
}	
