#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CRLF "\r\n"
#define BUF_SIZE 1024

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define MAX_USERS 100

/*************** les prototypes *************/
void cree_connexion(SOCKET *sock, SOCKADDR_IN *ssin, char * addr, int port);
static void ferme_connexion(const SOCKET sock);
void envoie(char *msg, SOCKET sock);
char* recoit(SOCKET* sock);
char * concatene(char* str, char c);
char * str_concatene(char* str, char* strc);
char** str_split(char* str, char delim);
char* saisie();
char * str_copy(char *chaine);
static int read_msg(SOCKET sock, char *buffer);
static void write_msg(SOCKET sock, const char *buffer);
static int init_connection(const char *address, const int port);

/************** les fonctions **************/

/* recevoir un message */
static int read_msg(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(errno);
   }
	//printf("%s\n",buffer);
   buffer[n] = '\0';
   

   return n;
}

/* envoyer un message*/
static void write_msg(SOCKET sock, const char *buffer){
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}


static int init_connection(const char *address, const int port){
	
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin;
   struct hostent *hostinfo;

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL)
   {
      fprintf (stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
   }

   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
   {
      perror("connect()");
      exit(errno);
   }
	printf("%d\n", sock);
   return sock;
}


void cree_connexion(SOCKET *sock, SOCKADDR_IN *ssin, char * addr, int port){
	WSADATA	WSAData;
  	WSAStartup(MAKEWORD(2,2),&WSAData);
  	*sock = socket(AF_INET, SOCK_STREAM, 0);
	(*ssin).sin_addr.s_addr = inet_addr(addr);
	(*ssin).sin_family = AF_INET;
	(*ssin).sin_port = htons(port);
	connect(*sock, (SOCKADDR*) ssin, sizeof(*ssin));
	printf("Connexion au serveur %s: %d...\n",inet_ntoa((*ssin).sin_addr), port);
}

static void ferme_connexion(const SOCKET sock){
	closesocket(sock);
	
}

void envoie(char *msg, SOCKET sock){
	unsigned int taille = strlen(msg);
	//char t [] = { taille };  
	//if(send(sock, t, sizeof(taille), 0) != -1){
		send(sock, msg, taille, 0);
	
}

char* recoit(SOCKET sock){
	char *recu  = "";
	char buffer [200];
 
	int taille = 200;
	int err = 2;
//	char t [32] = "";
	//recv(sock, t, 32, 0); //la taille des donnees
	//taille = atoi(t[0]);
	//if(err != -1){
	int lue = 0;
	//do{
	recv(sock, recu, taille, 0); //reception des donnees
		//if(buffer != NULL && err != -1)
		//	recu = str_concatene(recu, buffer);
			
	//}while(true);
	//fflush(sock);
	return recu;
}

char* recoitt(SOCKET sock){
	char *recu  = "";
	char buffer [100];
 
	unsigned int taille = 100;
	int err = 2;
//	char t [32] = "";
	//recv(sock, t, 32, 0); //la taille des donnees
	//taille = atoi(t[0]);
	//if(err != -1){
	int lue = 0;
	do{
		err= recv(sock, buffer, taille, 0); //reception des donnees
		if(buffer != NULL && err != -1)
			recu = str_concatene(recu, buffer);
			
	}while(true);

	return recu;
}

char * concatene(char* str, char c){
	int t=strlen(str);
	char * res = (char*) malloc(sizeof(char)*(t+1));
	int i=0; 
	for(i=0; i<t; i++)
		res[i] = (char) str [i];
	res[t] = c;
	return res;
}

char * str_concatene(char* str, char* strc){
	/*int t=strlen(str);
	int tc=strlen(strc);*/
	
	char* res ; //= (char*) malloc(sizeof(char)*(t+tc));
	/*int i=0;
	for(i=0; i<t; i++)
		res[i] = str[i];
	for(i=0; i<tc; i++)
		res[i+t] = strc[i];*/
	
	res = strcat(str, strc);
	
	return res;
}

char * str_copy(char *chaine){
	int t =strlen(chaine);
	char * res = (char*) malloc(sizeof(char)*t);
	int i=0;
	for(i=0; i<t; i++){
		res[i] = chaine[i];
	}
	
	return res;
}

char** str_split(char* str, char delim){
	
	int t = strlen(str);
	int nb_tokens = 1;
	int i=0;
	for(i=0; i<t; i++){
		if(str[i] == ' ')
			nb_tokens++;
	}

	char ** tab_res = (char**) malloc(sizeof(char*)*nb_tokens);
	int index = 0;
	for(i=0; i<nb_tokens; i++){
		tab_res[i] = "";
		
		char c;
		do{
			c = str[index];
			if(c != ' ' && c != '\0')
				tab_res[i] = concatene(tab_res[i],c);
			index++;
		}while(c != ' ' && c != '\0');
	}
	return tab_res;
}

void purger(){
	char c;

	while((c=getchar()) != '\n' && c != EOF){
		
	}
}

void clean(){

}