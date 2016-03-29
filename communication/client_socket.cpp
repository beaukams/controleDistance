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

#define PORT 20019


void creeSocket(SOCKET *sock, SOCKADDR_IN *ssin, char * addr, int port){
	WSADATA	WSAData;
  	WSAStartup(MAKEWORD(2,2),&WSAData);
  	*sock = socket(AF_INET, SOCK_STREAM, 0);
	*ssin.sin_addr.s_addr = inet_addr(addr);
	*ssin.sin_family = AF_INET;
	*ssin.sin_port = htons(port);
	connect(*sock, (SOCKADDR*) ssin, sizeof(*ssin));
}

void fermeSocket(SOCKET *sock){
	closesocket(sock);
	WSACleanup();
}

void envoie(char *msg, SOCKET sock){
	int taille = (int)strlen(msg)+1;
	if(send(sock, &taille, sizeof(taille), 0)){
		int err=send(sock, msg, taille, 0);
	}

}

char* recoit(SOCKET sock){
	char *recu; 
	int err, taille;
	do{
		err=recv(sock, &taille, sizeof(taille), 0);
		recv(sock, recu, sizeof(taille), 0);
	}while(err);

	return res;
}


void main(int argc, char **args){
	#if defined (WIN32)
		
	#endif
	
	//creation et parametrage du socket
	SOCKET sock ;
	SOCKADDR_IN ssin;
	
	
	//etablir une communication
	
	printf("Connexion au serveur %s: %d...\n",inet_ntoa(ssin.sin_addr), PORT);

	printf("fermeture de la socket serveur\n");
	
}
