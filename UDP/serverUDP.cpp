#include "include/SocketUDP.hpp"

int main(int argc, char*argv[]){
	if(argc!=3){
		printf("USAGE: %s PORT MSG\n",argv[0]);
		return -1;
	}
	int port=atoi(argv[1]);
	char*msg=argv[2];	
	
	SocketUDP myself(port,true);
	Address address;
	char* buffer = myself.ricevi(&address);
	if(!buffer){
		errore(-2,"ricevi");
		
	}
	printf("msg:%s\n", buffer);
	
	if(myself.invia(msg, address)){
		errore(-3, "invia()");
	}
	
	free(buffer);
	return 0;	
}
