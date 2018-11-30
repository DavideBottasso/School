/* programmino che implementa una chat mediante SocketUDP.hpp 
 provate a vedere se compila ma...
 ...RICORDATE di passare -lpthread al g++ */

#include <cstdio> 
#include "SocketUDP.hpp"
#include "mylib.h"
#include <pthread.h> 

#define EXIT_CMD "exit"

void* listener(void*);

int main(int argc, char *argv[]) {
	if (argc!=3) {
		printf("USAGE:%s PORT BROADCAST_IP\n", argv[0]);
		return (-1);
	}

	int port = atoi(argv[1]);
	char* ip_broadcast = argv[2];

	SocketUDP* myself = new SocketUDP();
	myself->setBroadcast(true);

	pthread_t t_listener;
	pthread_create(&t_listener, NULL, listener, myself);

	Address broadcast(ip_broadcast, port);

	char* command;
	
	while(cmpStr(command = inputStr(), EXIT_CMD)) {
		if (myself->invia(broadcast, command))	
			error("invia()", 2);
		free(command);
	}

	/* pthread_cancel(t_listener); */

	free(command);
	delete(myself);

	return 0;
}

void* listener(void* param) {
	SocketUDP* myself = (SocketUDP*) param;

	char* message;
	Address sender;

	while(true) {
		message = myself->ricevi(&sender);
		if (!message)	
			error("ricevi()", -3);

		char* sender_descr = sender.toString();
		printf("[%s]%s\n", sender_descr, message);
		
		free(sender_descr);
		free(message);
	}
}
