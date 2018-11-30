#include "/SocketUDP.hpp"
int main(int argc, char*argv[]{
	if(argc!=4){
		printf("USAGE: %s IP PORT MESSAGE\n", argv[0]);
		return -1;
	}
	char*ip=argv[1];//è istanziato in modo statico
	int port=atoi(argv[2]);//è istanziato in modo statico
	char*msg=argv[3];//è istanziato in modo statico
	
	Address server(ip, port); //è istanziato in modo statico
	
	SocketUDP myself; //è istanziato in modo statico
	
	//maniglia freccina, istanza punto
	if(myself.invia(msg, server));
	errore(-2, "message");
	
	Address mittente;
	char*buffer=myself.ricevi(&mittente);//è istanziato in modo dinamico
	if(!buffer){
		errore(-3, "ricevi");
		printf("MSG:%s\n",buffer);
	}
	
	free(buffer);
	
	return 0;	
}
