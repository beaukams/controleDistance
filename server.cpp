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

void creer();


int main(int argc, char **args){

	#if defined (WIN32)
		WSADATA	WSAData;
  		WSAStartup(MAKEWORD(2,2),&WSAData);
	#endif

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
	bind(sock, (SOCKADDR*) &ssin, sizeof(ssin));
	listen(sock, 5);

	socklen_t taille = sizeof(ccsin);
	csock = accept(sock, (SOCKADDR*)&ccsin, &taille);
	printf("connexion du client %s:%d...\n", inet_ntoa(ccsin.sin_addr), htons(ccsin.sin_port));
	//fermer la connexion
	printf("fermeture de la socket client\n");
	closesocket(csock);

	printf("fermeture de la socket serveur\n");
	closesocket(sock);

  	#if defined	(WIN32)
		WSACleanup();
	#endif
	return EXIT_SUCCESS;
}
