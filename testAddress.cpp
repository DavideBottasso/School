#include "Address.hpp"
int main(int argc, char const *argv[]){
	
	cahr* temp;
	
	Address indirizzo("192.168.0.1", 8080);
	Address*maniglia;
	
	indirizzo.setPort(8888);
	
	maniglia = new Address(indirizzo);
	maniglia->setIp("127.0.0.1");
	
	temp = indirizzo.tostring();
	printf"Ho creato %s\n", temp;
	free(temp);
	
	printf("Ho anche stampato %s\n", temp=maniglia->tostring());
	
	delete(maniglia);
	
	return 0;
}