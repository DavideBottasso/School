#include "Address.hpp"
#include <string.h>
#include "mylib.h"

#define PORT_SERVER 1026
#define MAX_MSG 4096

int main(int argc, char* argv[]){

    int socketid;
    socketid = socket(AF_INET, SOCK_DGRAM, 0);
    if(socketid < 0){
        errore(-1, "socket()");
    }

    Address server(IP_DHCP, PORT_SERVER);
    struct sockaddr_in addrServer = server.getBinary();

    char msg[] = "Client";
    int ret = sendto(socketid, msg, lenstr(msg) + 1, 0
                (struct sockaddr)&addrServer,
                (socklen_t)sizeof(struct sockaddr_in) );
    if(ret != lenstr(msg) +1) errore(-2, "sendto()");

    char buffer[MAX_MSG +1];
    //struct sockaddr_in mitAddr;
    int addrLen = sizeof(struct sockaddr_in);
    ret = recvfrom(socketid, buffer, MAX_MSG, 0,
                (struct sockadd)&addrServer,
                (socklen_t*)&addrLen);
    if(ret <= 0) errore(-3, "recv()");
    //Address mittente(mitAddr);
    char* mittStr = server.toString();
    buffer[ret] = '\0';
    printf("%s: '%s'\n", mittStr, buffer);
    free(mittStr);

    close(socketid);


    return 0;
}