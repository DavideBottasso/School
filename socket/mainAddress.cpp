#include "Address.hpp"

/*Testing values*/
#define IP_ADDRESS 192.168.0.1
#define PORT 1026

/*
	TEST METODI

	CONTROLLARE FREE
	INSERIRE free(ret);
*/

char* testSetIp(Address* indirizzo);
char* testSetPort(Address* indirizzo);
char* testGetIp(Address* indirizzo);
char* testGetPort(Address* indirizzo);
char* testToString(Address* indirizzo);
char* testAddress();
char* testAddress(Address* indirizzo);
char* testAddress_sockaddr();
char* testSetBinary(Address* indirizzo);
char* testGetBinary(Address* indirizzo);

int main(int argc, char const *argv[]){

	Address indirizzo(IP_ADDRESS, PORT);

	printf("%s\n",testGetIp(indirizzo));
	printf("%s\n",testGetPort(indirizzo));
	printf("%s\n",testSetIp(indirizzo));
	printf("%s\n",testSetPort(indirizzo));
	printf("%s\n",testToString(indirizzo));
	printf("%s\n",testAddress());
	printf("%s\n",testAddress(indirizzo));


	return 0;
}

char* testSetIp(Address* indirizzo){
	char* ret;
	ret = strdup("Address::setIp() : failed");

	char* temp;

	temp=strdup("192.168.1.10");
	indirizzo->setIp(temp);
	if(strcmp(indirizzo->getIp(), temp) == 0){
		free(ret);
		ret = strdup("Address::setIp() : successful");;
	}

	free(temp);
	return strdup(ret);
}

char* testSetPort(Address* indirizzo){
	char* ret;
	ret = strdup("Address::setPort() : failed");

	int temp = 1025;

	indirizzo->setPort(temp);
	if(indirizzo->getPort() == temp){
		ret = strdup("Address::setPort() : successful");
	}

	return strdup(ret);
}

char* testGetIp(Address* indirizzo){
	char* ret;
	ret = strdup("Address::getIp() : failed");

	if(indirizzo->getIp() == IP_ADDRESS){
		ret = strdup("Address::getIp() : successful");;
	}

	return strdup(ret);
}

char* testGetPort(Address* indirizzo){
	char* ret;
	ret = strdup("Address::getPort() : failed");

	if(indirizzo->getPort() == PORT){
		ret = strdup("Address::getPort() : successful");;
	}

	return strdup(ret);
}

char* testToString(Address* indirizzo){
	char* ret;
	ret = strdup("Address::toString() : failed");

	char* tempAddress[25];
	//sprintf(tempAddress, "[%s:%d]", newIp, newPort);

	char* tempTest;
	tempTest = indirizzo.toString();
	if(strcmp(tempAddress, tempTest) == 0){
		ret = strdup("Address::toString() : successful");
	}

	return strdup(ret);	
}

char* testAddress(){
	char* ret;
	ret = strdup("Address::Address() : failed");

	char tempStr[25];
	char testStr[25];

	testStr = strdup("[127.0.0.1:0]");
	Address* indirizzo = new Address();
	tempStr = indirizzo->toString();
	if(strcmp(tempStr, testStr)){
		ret =  strdup("Address::Address() : successful";
	}

	return strdup(ret);
}

char* testAddress(Address* indirizzo){
	char* ret;
	ret = strdup("Address::Address(const Address& a) : failed");
	Address testIndirizzo;

	testIndirizzo = new Address(indirizzo);
	if(strcmp(indirizzo->toString(), indirizzo.toString())){
		ret = strdup("Address::Address(const Address& a) : successful");
	}

	return strdup(ret);
}

char* testAddress_sockaddr(){
	char* ret;
	ret = strdup("Address:Address(const sockaddr_in& a : failed");

	Address testIndirizzo;
	char* testIp;
	testIp = strdup("127.0.0.1");
	struct sockaddr_in testStruct;
	testStruct= (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));

	testStruct.sin_family = AF_INET;
	inet_aton(testIp, testStruct.sin_addr);
	testStruct.sin_port = htons(0);
	for(int i=0; i < 8; i++){
		testStruct.sin_zero[i] = 0;
	}

	testIndirizzo = new Address(testStruct);
	if(strcmp(testIndirizzo.toStringl, strdup("[127.0.0.1:0]")) == 0){
		ret = strdup("Address:Address(const sockaddr_in& a) : successful");
	}

	return strdup(ret);
}

char* testSetBinary(Address* indirizzo){
	char* ret;
	ret = strdup("Address::setBinary(struct sockaddr a) : failed");

	char* testIp;
	testIp = strdup("127.0.0.1");
	struct sockaddr_in testStruct;
	testStruct= (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));

	testStruct.sin_family = AF_INET;
	inet_aton(testIp, testStruct.sin_addr);
	testStruct.sin_port = htons(0);
	for(int i=0; i < 8; i++){
		testStruct.sin_zero[i] = 0;
	}

	indirizzo->setBinary(testStruct);
	if(strcmp(indirizzo->toString, strdup("[127.0.0.1:0]")) == 0){
		ret = strdup("Address::setBinary(struct sockaddr a) : successful");
	}

	return strdup(ret);
}

char* testGetBinary(Address* indirizzo){
	char* ret;
	ret = strdup("Address::getBinary() : failed");

	char* testIp;
	testIp = indirizzo->getIp();
	int testPort = indirizzo->getPort();

	struct sockaddr_in testStruct;

	testStruct = indirizzo->getBinary();

	if(ntohs(testStruct.sin_port) == testPort){
		if(strcmp(inet_ntoa(testStruct.sin_addr), testIp) == 0){
			ret = strdup("Address::getBinary() : successful");
		}
	}

	return strdup(ret);
}