#ifndef __SOCKET_UDP_HPP
#define __SOCKET_UDP_HPP

class Socket_UDP{
	private: int socket_id;
	public: 
			SocketUDP(Address);
			
			bool invia(Address, char*);
			char* ricevi(Address*);
			
			~SocketUDP();
}

SocketUDP::SocketUDP();
SocketUDP::SocketUDP(Address myself);

bool SocketUDP::invia(Address dest, char* message);
char*SocketUDP:: ricevi(Address*);

~SocketUDP();

#endif __SOCKET_UDP_HPP
