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

	//declaration du socket et du thread
	SOCKET sock ;
	SOCKADDR_IN ssin;
	//pthread_t thread;

	creeSocket(&sock, &ssin, addr, port);
	
//	pthread_create(&thread, NULL, get_response, (void*) &sock);

	char* msg="";
	char* recu = "";
	do{
		msg = saisie();
		printf("message envoye: %s \n",msg);
		envoie(msg, sock);
		if(strcmp(msg, "exit") == 0)
			break;
		
		/*recu = recoit(sock);
		printf("%s \n", recu);
		recu = "";
		msg="";*/
	}while(true);

	fermeSocket(sock);
}

