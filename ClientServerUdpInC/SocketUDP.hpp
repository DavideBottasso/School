/*
Implementare client e server per inviare file
indirizzo ip, porta e nome del file da spedire
Broadcast: indirizzo comune a più macchine
setsockopt()
metodo da chiamare gli passo il 
*/
#ifndef __SOCKETUDP_HPP
#define __SOCKETUDP_HPP

#define BUFSIZE 4096

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Address.hpp"
#include "../lib/mylib.h"
#include <iostream>
#include <fstream>

class SocketUDP {
private:
    int sockid;

public:
    SocketUDP();
    SocketUDP(Address mySelf);
    int sockkid();
    bool invia(Address dest, const char* msg);
    bool inviaRaw(Address dest, const char* msg, int numByte);
	bool inviaFile(Address, char* path);
    char* ricevi(Address&);
    char* riceviRaw(Address&, int* nBytes);
    bool riceviFile(Address*,char*path, int nByte);
    void nSocketUDP();
    ~SocketUDP();
};
/*--------------------------------------------*/
int SocketUDP::sockkid()
{
    sockid = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockid < 0)
        error("ERRORE non sono riuscito ad aprire il socket");
    return sockid;
}

/*--------------------------------------------*/

SocketUDP::SocketUDP()
{
    /*sockid = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockid < 0) 
    error("ERRORE non sono riuscito ad aprire il socket");*/
}
/*--------------------------------------------*/
SocketUDP::SocketUDP(Address mySelf)
{
    int socketid = sockkid();
    printf("%d", socketid);
    struct sockaddr_in myself_addr = mySelf.getSockaddr_in();
    if (bind(socketid, (struct sockaddr*)&myself_addr,
            sizeof(struct sockaddr_in))
        < 0) {
        error("ERRORE non sono riuscito in binding");
    }
}
/*--------------------------------------------*/
bool SocketUDP::invia(Address dest, const char* msg)
{
    struct sockaddr_in serveraddr = dest.getSockaddr_in();
    int ret = sendto(sockid, msg, strlen(msg), 0,
        (struct sockaddr*)&serveraddr, (socklen_t)sizeof(struct sockaddr_in));
    if (ret < 0) {
        return false;
    }
    else {
        return true;
    };
}

/*--------------------------------------------*/
char* SocketUDP::ricevi(Address& mitt)
{
    char buff[BUFSIZE + 1];
    int clientlen = (socklen_t)sizeof(struct sockaddr_in);
    bzero(buff, BUFSIZE + 1);
    struct sockaddr_in mittente;
    int ret = recvfrom(sockid, buff, BUFSIZE, 0,
        (struct sockaddr*)&mittente, (socklen_t*)&clientlen);
    if (ret < 0)
        error("ERRORE in recvfrom");
    buff[ret] = '\0';
    mitt.setSockaddr_in(mittente);
    return strdup(buff);
}
/*--------------------------------------------*/
bool SocketUDP::inviaRaw(Address dest, const char* msg, int numByte)
{
    struct sockaddr_in serveraddr = dest.getSockaddr_in();
    int ret = sendto(sockid, msg, numByte, 0,
        (struct sockaddr*)&serveraddr, (socklen_t)sizeof(struct sockaddr_in));
    if (ret < 0) {
        return false;
    }
    else {
        return true;
    };
}
/*--------------------------------------------*/
char* SocketUDP::riceviRaw(Address& mitt, int* nBytes)
{
    char buff[BUFSIZE + 1];
    int clientlen = (socklen_t)sizeof(struct sockaddr_in);
    bzero(buff, BUFSIZE + 1);
    struct sockaddr_in mittente;
    int ret = recvfrom(sockid, buff, BUFSIZE, 0,
        (struct sockaddr*)&mittente, (socklen_t*)&clientlen);
    if (ret < 0)
        error("ERRORE in recvfrom");
    buff[ret] = '\0';
    mitt.setSockaddr_in(mittente);
    *nBytes = ret;
    return strdup(buff);
}
bool SocketUDP::inviaFile(Address, char* path)
{
	string line;
	ifstream myfile path);
  	if(myfile.is_open()){
    	while(getline(myfile,line)){
			struct
    	}
    myfile.close();
    return false;
	}
 	else return true;
}
/*--------------------------------------------*/
bool SocketUDP::riceviFile(Address*, char*path, int nByte)
{

}

/*--------------------------------------------*/


/*--------------------------------------------
void SocketUDP::nSocketUDP(){
   int ret = close(sockid);
   if(ret){ error("Errore In chiusura");}else{printf("Socket Chiuso\n");}
}
*/
SocketUDP::~SocketUDP()
{
    close(sockid);
}
#endif //__SOCKETUDP_HPP





















