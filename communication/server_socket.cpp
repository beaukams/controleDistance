/**communications clients avec les sockets TCP en C.
* AUTHORS: 
*/
//Si nous sommes sous Windows
#include <winsock2.h>
typedef int socklen_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <conio.h>
#include "util.c"

#define PORT 20019


void* un_client(void * sock){
	char* msg= "";
	do{
		msg = recoit((int) sock);
		msg = str_concatene("COMMANDE ",msg);
		system(msg);

		//reponse
		
	}while( strcmp(msg, "EXIT") || strcmp(msg, "exit"));


	//fermer la connexion
	printf("fermeture de la socket client\n");
	closesocket(csock);

	pthread_exit(NULL);
}


void main(int argc, char **args){
	
	
	WSADATA	WSAData;
  	WSAStartup(MAKEWORD(2,2),&WSAData);
	
	//creation et parametrage du socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET csock;
	SOCKADDR_IN ssin, ccsin;
	ssin.sin_addr.s_addr = inet_addr("127.0.0.1");
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(PORT);

  	//code a executer
  	printf("Demarrage du serveur sur le port %d...\n", PORT);	
	
	//etablir une communication
	int err_bind = bind(sock, (SOCKADDR*) &ssin, sizeof(ssin));
	listen(sock, 5);	

	socklen_t taille = sizeof(csin);

	while(true){
		csock = accept(sock, (SOCKADDR*)&ccsin, &taille);

		printf("connexion du client %s:%d...\n", inet_ntoa(ccsin.sin_addr), htons(ccsin.sin_port));

		//creation d'un thread pour gerer le client
		pthread_t client;
		int err_thr = pthread_create(&client, NULL, un_client, (void*) &csock);

		
	}
	

	printf("fermeture de la socket serveur\n");


	closesocket(sock);
  	
	WSACleanup();
	
}
