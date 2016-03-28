/**communications clients avec les sockets TCP en C.
* AUTHORS: 
*/
//Si nous sommes sous Windows
#if defined (WIN32)
	#include <winsock2.h>
  	typedef int socklen_t;

#elif defined (linux)
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>

	#define	closesocket(param) close(param) 
	#define	INVALID_SOCKET -­1
	#define	SOCKET_ERROR -­1

	typedef	int	SOCKET;
	typedef	struct sockaddr_in SOCKADDR_IN;
	typedef	struct sockaddr	SOCKADDR;

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>

#define PORT 20019




void main(int argc, char **args){
	
	#if defined (WIN32)
		WSADATA	WSAData;
  		WSAStartup(MAKEWORD(2,2),&WSAData);
	#endif

	//creation et parametrage du socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET csock;
	SOCKADDR_IN ssin, csin;
	ssin.sin_addr.s_addr = inet_addr("127.0.0.1");
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(PORT);

  	//code a executer
  	printf("Demarrage du serveur sur le port %d...\n", PORT);	
	
	//etablir une communication
	bind(sock, (SOCKADDR*) &ssin, sizeof(ssin));
	listen(sock, 5);	

	socklen_t taille = sizeof(csin);
	csock = accept(sock, (SOCKADDR*)&csin, &taille);
	printf("connexion du client %s:%d...\n", inet_ntoa(csin.sin_addr), htons(csin.sin_port));
	//fermer la connexion
	printf("fermeture de la socket client\n");
	closesocket(csock);

	printf("fermeture de la socket serveur\n");
	closesocket(sock);

  	#if defined	(WIN32)
		WSACleanup();
	#endif
}
