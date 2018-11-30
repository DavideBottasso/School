#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/Address/ADDRESS.h"
#include "../../lib/Error.h"

#define MAX_MESSAGE_LEN 4096

//prototipi
int creaSoket();
void invia(int socketId);

int main(int argc, char** argv)
{
    //variabili locali
    char* serverIp;
    int serverPort;
    char* message;

    /*parametri della shell*/
    if(argc!=4)
    {
        printf("\n  USAGE: %s server_ip server_port \"message\"", argv[0]);
        return -1;
    }

    serverIp = argv[1];
    serverPort = atoi(argv[2]);
    message = argv[3];

    /*implementazione client*/
    int socketId = creaSocket();
    invia(socketId, serverIp, serverPort, message);
    struct sockaddr server = ricevi(socketId);
    close(socketId);
}

int creaSoket()
{
    printf("\n  creazione del soket...");
    int ret = socket(AF_INET, SOCK_DGRAM, 0);
    if(ret<0) error(-1, "socket()");
    printf("Creato\n");

    return ret;
}

void invia(int socketId, char* ip, int port, char* message)
{
    Address addrServer = Address(ip, port);
    struct sockaddr server = addrServer.toSockaddr();
    printf("Invio del messaggio al socket %s...", addrServer.toString());

    int ret = sendto(socketId, message, strlen(message)+1, 0, (struct sockaddr*) &server, (socklen_t) sizeof(struct sockaddr_in));

    if(ret != strlen(message)+1) error(-2, "sendto()");

    printf("Inviato");
}

struct sockaddr ricevi(int socketId)
{
    printf("\n  In attesa di un messaggio di conferma...");

    char buffer[MAX_MESSAGE_LEN+1];
    struct sockaddr server;
    int socklen = sizeof(struct sockaddr_in);

    int ret = recvfrom(socketId, buffer, MAX_MESSAGE_LEN, 0, (struct sockaddr*) server, (socklen_t)&socklen);

    if(ret<=0) error(-3, "recvfrom()");

    printf("Confermato\n");

    return server;
};
