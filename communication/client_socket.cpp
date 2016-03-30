/**communications clients avec les sockets TCP en C.
* AUTHORS: 
*/
//Si nous sommes sous Windows

#include <winsock2.h>
typedef int socklen_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include "util.c"

#define PORT 20019


void main(int argc, char **args){
	//creation et parametrage du socket
	char * addr = "127.0.0.1";
	int port = 20019;

	SOCKET sock ;
	SOCKADDR_IN ssin;

	creeSocket(&sock, &ssin, addr, port);
	char* msg="";
	do{
		gets(msg);
		envoie(msg);
		if(strcmp(msg, "exit") == 0)
			break;

	}while(true);

	fermeSocket(sock);
}
