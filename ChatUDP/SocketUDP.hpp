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
#include "mylib.h"

class SocketUDP {
private:
    int sockid;

public:
    SocketUDP();
    SocketUDP(Address mySelf);
    int sockkid();
    bool setBroadcast(bool set);
    bool invia(Address dest, char* msg);
    void* ricevi(Address*);

    bool inviaRaw(Address dest, void* msg, int numByte);
    void* riceviRaw(Address*, int* nBytes);

    bool inviaFile(char* path , Address dest);
    void* riceviFile(char* path);


    void nSocketUDP();
    ~SocketUDP();
};
/******************************/
int SocketUDP::sockkid()
{
    sockid = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockid < 0)
        error("ERRORE non sono riuscito ad aprire il socket", -1);
    return sockid;
}

/******************************/

SocketUDP::SocketUDP()
{
  sockid = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockid < 0)
    error("ERRORE non sono riuscito ad aprire il socket", -2);
}
/******************************/
SocketUDP::SocketUDP(Address mySelf)
{
    int socketid = sockkid();
    printf("%d", socketid);
    struct sockaddr_in myself_addr = mySelf.getSockaddr_in();
    if (bind(socketid, (struct sockaddr*)&myself_addr,
            sizeof(struct sockaddr_in))
        < 0) {
        error("ERRORE non sono riuscito a bindare", -3);
    }
}
/******************************/
bool SocketUDP::invia(Address dest, char* msg)
{
   	return inviaRaw(dest,msg,strlen(msg));
}

/******************************/
void* SocketUDP::ricevi(Address* mitt)
{
  int size;
  char* raw_buff = (char*)riceviRaw(mitt, &size);
  char* ret = (char*)malloc(sizeof(char*) * (size+1));
  memcpy(ret,raw_buff,size);
  ret[size] = '\0';
  return ret;
}
/******************************/
bool SocketUDP::inviaRaw(Address dest, void* msg, int numByte)
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
/******************************/
void* SocketUDP::riceviRaw(Address *mitt, int* nBytes)
{

	    char buff[BUFSIZE + 1];
	    int clientlen = (socklen_t)sizeof(struct sockaddr_in);
	    bzero(buff, BUFSIZE + 1);
	    struct sockaddr_in mittente;
	    int ret = recvfrom(sockid, buff, BUFSIZE, 0,
		(struct sockaddr*)&mittente, (socklen_t*)&clientlen);
	    if (ret < 0)
		error("ERRORE in recvfrom", -4);
	    mitt->setSockaddr_in(mittente);
	    *nBytes = ret;
	    return strdup(buff);
}
/******************************/
bool SocketUDP::inviaFile(char* path , Address dest)
{
	int i=0;
  char ch;
  printf("%s\n",path);
  int nPacchetti=0;
  FILE* fp = fopen(path,"r");
  if(fp == NULL){
		int n_packet = 0;
	  inviaRaw(dest,&n_packet,(int)sizeof(int));
		return true;
	}

  printf("HWLOOOOO\n");
    fseek(fp,0,SEEK_END);
  	int file_size=ftell(fp);
  	fseek(fp,0,SEEK_SET);
    nPacchetti =(BUFSIZE<file_size) ? file_size/BUFSIZE : (file_size/BUFSIZE) +1;
    printf("%d\n",nPacchetti);
    inviaRaw(dest,&nPacchetti,(int)sizeof(int));
    int sizePacc, temp=file_size;
    for(int i= 0; i<nPacchetti; i++){
     char file_buffer[BUFSIZE];
     sizePacc= ( (temp%BUFSIZE) == 0) ? BUFSIZE : (file_size%BUFSIZE);
     printf("%d\n",sizePacc);
     fread(file_buffer,sizePacc,1,fp);
      /*while (fgets(file_buffer, sizePacc, fp) != NULL){
        printf("%s", file_buffer);
      }*/
      temp-=sizePacc;
      inviaRaw(dest,file_buffer,sizePacc);

  	}
  fclose(fp);
	return false;

}
/******************************/
void* SocketUDP::riceviFile(char* path){
	FILE * fp = fopen(path,"w");
	int size;
	int size_tot=0;
  Address mit;
	int* n_packet = (int*)riceviRaw(&mit,&size);

  for(int i= 0; i< *n_packet; i++){
	    char* buffer = (char*) riceviRaw(&mit,&size);
      printf("%s\n",buffer);
      printf("%d\n",size);
      size_tot+= size;
      printf("%d\n",size_tot);
		  fwrite(buffer,size,1,fp);
	}
	fclose(fp);
	return (void*)size_tot;

}
/******************************/
bool SocketUDP::setBroadcast(bool set){
	int broadcastPermission=1;
	if(set){
		if (setsockopt(sockid, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,sizeof(broadcastPermission)) < 0){
       		    error( "setsockopt error", -4);

   		}
      return false;
	}
}


/******************************
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
