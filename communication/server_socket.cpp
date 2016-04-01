/**communications clients avec les sockets TCP en C.
* AUTHORS: 
*/
//Si nous sommes sous Windows
#include <winsock2.h>
typedef int socklen_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.c"
#include <process.h>
#include <errno.h>

#define PORT 20019

#define CRLF "\r\n"
#define BUF_SIZE 1024

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define MAX_USERS 5

static int init_server(const int port);
static void app(int port);

typedef struct {
	SOCKET sock;
}Utilisateur;

void un_client(SOCKET *ssock){
	char* msg= "";
	char * com = "COMMANDE ";
	SOCKET sock = (SOCKET) *ssock;
	do{
		msg = recoit(sock);
		printf(" ");
		fflush(stdin);
		//fflush(stdout);
		char *message = str_concatene(com,msg);
		printf("Message: %s \n", message);
	/*	system(message);

		//lecture du resultat
		FILE* fichier = fopen("fichierUser.txt", "r");
		char *ch = "";
		char* res = "";
		while(fgets(ch, 1000, fichier) != NULL)
			res = str_concatene(res, ch);
		fflush(fichier);
		fclose(fichier);
		
		//reponse
		envoie(res, sock); 
		
		//reset
		msg="";*/
		
	}while(strcmp(msg, "EXIT") || strcmp(msg, "exit"));


	//fermer la connexion
	printf("fermeture de la socket client\n");
	closesocket(sock);

	//pthread_exit(NULL);
}


void main(int argc, char **args){
	
	
	WSADATA	WSAData;
  	WSAStartup(MAKEWORD(2,2),&WSAData);
	
	int port = PORT;
	if(argc > 1){
		port = atoi(args[1]);
	}
	
	app(port);
  	
	WSACleanup();
	
}


static void app(int port){
   SOCKET sock =  init_server(port);
   printf("Demarrage du serveur sur le port %d...\n", port);
   char buffer[BUF_SIZE];

   fd_set rdfs;
   
   int actual = 0;
   int max = sock;
   Utilisateur users[MAX_USERS];

   while(1)
   {
		
      int i = 0;
      FD_ZERO(&rdfs);

    //  FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(sock, &rdfs);

		
      /* add socket of each client */
      for(i = 0; i < actual; i++)
      {
         FD_SET(users[i].sock, &rdfs);
      }

      if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      if(FD_ISSET(sock, &rdfs))
      {
         /* new client */
         SOCKADDR_IN csin = { 0 };
         socklen_t sinsize = sizeof csin;
         SOCKET csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
         if(csock == SOCKET_ERROR)
         {
            perror("accept()");
            continue;
         }

		 printf("Connexion au du client %s: %d...\n",inet_ntoa(csin.sin_addr), csin.sin_port);
		 fflush(stdout);
       /*  /* after connecting the client sends its name */
    //     if(read_msg(csock, buffer) == -1)
      //   {
            /* disconnected */
        //    continue;
         //}

         /* what is the new maximum fd ? */
         max = csock > max ? csock : max;

         FD_SET(csock, &rdfs);

         Utilisateur c = { csock };
        // strncpy(c.name, buffer, BUF_SIZE - 1);
         users[actual] = c;
         actual++;
      }
      else
      {
         int i = 0;
         for(i = 0; i < actual; i++)
         {
            /* a client is talking */
            if(FD_ISSET(users[i].sock, &rdfs))
            {
               Utilisateur user = users[i];
               int c = read_msg(users[i].sock, buffer);
			   printf("recu: %s", buffer);
               /* client disconnected */
               if(c == 0)
               {
                  ferme_connexion(user.sock);
               }
               else
               {
                 
					char* msg = "bien recu";
					printf("envoie: %s\n",msg);
					write_msg(user.sock,  msg);
               }
               break;
            }
         }
      }
   }
   
   ferme_connexion(sock);
   printf("fermeture de la socket serveur\n");
   
}

static int init_server(const int port)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin;

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   sin.sin_addr.s_addr = inet_addr("127.0.0.1");
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
   {
      perror("bind()");
      exit(errno);
   }

   if(listen(sock, MAX_USERS) == SOCKET_ERROR)
   {
      perror("listen()");
      exit(errno);
   }


   return sock;
}
