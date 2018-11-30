#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/Address/ADDRESS.h"
#include "../../lib/Error.h"

#define MAX_MESSAGE_LEN 4096
#define CONFIRM_MESSAGE "conferma"

//prototipi
int creaSocket();
struct sockaddr associaSocket(int socketID);
struct sockaddr ricevi(int socketId);
void invia(int socketId, struct sockaddr client);

int main(int argc, char** argv)
{
    socketId = creaSocket();
    struct sockaddr mySelf = associaSocket(sockerId);
    struct sockaddr client = ricevi(socketId);
    invia(socketId, client);
    close(socketId);
}

int creaSocket()
{
    int socketId;
    printf("\n  Apertura del socket...");
    socketId = socket(AF_INET, SOCK_DGRAM, 0);
    if(socketId <0 ) error(-1, "socket()");
    printf("  Creato");
}

struct sockaddr associaSocket(int socketID)
{
    printf("\n  Associazione del canale socket all'ip assegnato a questo terminale e alla porta %d", PORT_MYSELF);
        Address addrMySelf = Address(IP_LOOPBACK, PORT);
    struct sockaddr mySelf = addrMySelf.toSockaddr();

    int ret = bind(socketID, (struct sockaddr*) &mySelf, (socklen_t) sizeof(struct sockaddr_in)));
    if(ret!=0) error(-2, "bind()");
    printf("  Associato");

    return mySelf;
};

struct sockaddr ricevi(int socketId)
{
    printf("\n  In ascolto...");

    char buffer[MAX_MESSAGE_LEN+1];
    struct sockaddr_in clientSocket;
    int socklen;

    int ret = recvFrom(socketId, buffer, MAX_MESSAGE_LEN, 0, (struct sockaddr*) &clientSocket, (socklen_t)&socklen);
    if(ret<=0) error(-3, "recvFrom()");

    //recupero il messaggio ricevutok
    buffer[ret] = '/0';
    Address clientAddress = Address(clientSocket);
    char* clientToStr = clientAddress.toString();
    printf("\n  %s: %s", clientToStr, buffer);
    free(clientToStr);

    printf(" Ricevuto\n");

    return clientSocket;
};

void invia(int socketId, struct sockaddr client)
{
    printf("\n  Invio mesaaggio di conferma...");
    char* message = CONFIRM_MESSAGE;
    int ret = sendto(socketId, message, strlen(message), 0, &client, (socklen_t)sizeof(struct sockaddr_in));

    if(ret!=strlen(message)+1) error(-4, "sendto()");
    printf("Inviato\n");
}
