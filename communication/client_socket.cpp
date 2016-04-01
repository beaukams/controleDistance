/**communications clients avec les sockets TCP en C.
* AUTHORS: 
*/


//Si nous sommes sous Windows

#include <winsock2.h>
typedef int socklen_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "util.c"

#define PORT 20019
#define CRLF "\r\n"
#define BUF_SIZE 1024

#define QUIT "exit"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

static void init(void);
static void end(void);
static void app(const char *address, const int port);




int main(int argc, char **argv)
{
   if(argc < 2)
   {
      printf("Usage : %s [address] [port]\n", argv[0]);
      return EXIT_FAILURE;
   }

	WSADATA	WSAData;
	WSAStartup(MAKEWORD(2,2),&WSAData);
	
	app(argv[1], atoi(argv[2]));

	WSACleanup();
	return EXIT_SUCCESS;
}

static void app(const char *address, const int port){

   SOCKET sock = init_connection(address, port);
   char buffer[BUF_SIZE];

   //envoie de login et de mot de passe
 //  write_msg("login:abdoulaye");
   
   /* message de retour du serveur
   * 	si authentification réussie : prompt + message de bienvenue
   * 	sinon : message du type "veuillez vous authentifier"
   */
   

   while(1)
   {
		fgets(buffer, BUF_SIZE - 1, stdin);
		char* buff = buffer;
        if( strlen(buff) > 1 && buffer != NULL && buffer != "\n" && buffer != "\0" && buffer != "\r"){
			//fflush(stdin);
			write_msg(sock, buffer);
			//printf("envoie: %s", buffer);
         
      
			int n = read_msg(sock, buffer);
			/* server down */
			if(n == 0)
			{
				printf("Server disconnected !\n");
				break;
			}
			printf("recu: %s\n",buffer);
		}
      
   }

   ferme_connexion(sock);
}




