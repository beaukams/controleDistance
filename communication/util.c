#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*************** les prototypes *************/
void creeSocket(SOCKET *sock, SOCKADDR_IN *ssin, char * addr, int port);
void fermeSocket(SOCKET *sock);
void envoie(char *msg, SOCKET sock);
char* recoit(SOCKET* sock);
char * concatene(char* str, char c);
char * str_concatene(char* str, char* strc);
char** str_split(char* str, char delim);
char* saisie();

/************** les fonctions **************/

void creeSocket(SOCKET *sock, SOCKADDR_IN *ssin, char * addr, int port){
	WSADATA	WSAData;
  	WSAStartup(MAKEWORD(2,2),&WSAData);
  	*sock = socket(AF_INET, SOCK_STREAM, 0);
	(*ssin).sin_addr.s_addr = inet_addr(addr);
	(*ssin).sin_family = AF_INET;
	(*ssin).sin_port = htons(port);
	connect(*sock, (SOCKADDR*) ssin, sizeof(*ssin));
	printf("Connexion au serveur %s: %d...\n",inet_ntoa((*ssin).sin_addr), port);
}

void fermeSocket(SOCKET sock){
	closesocket(sock);
	printf("fermeture de la socket serveur\n");
	WSACleanup();
}

void envoie(char *msg, SOCKET sock){
	unsigned int taille = strlen(msg);
	//char t [] = { taille };  
	//if(send(sock, t, sizeof(taille), 0) != -1){
		send(sock, msg, taille, 0);
	
}

char* recoit(SOCKET sock){
	char recu [255];
 
	unsigned int taille = 255;
	int err = 2;
//	char t [32] = "";
	//recv(sock, t, 32, 0); //la taille des donnees
	//taille = atoi(t[0]);
	//if(err != -1){
	
	recv(sock, recu, taille, 0); //reception des donnees
	

	return recu;
}

char * concatene(char* str, char c){
	int t=strlen(str);
	char * res = (char*) malloc(sizeof(char)*(t+1));
	int i=0; 
	for(i=0; i<t; i++)
		res[i] = str [i];
	res[t] = c;
	return res;
}

char * str_concatene(char* str, char* strc){
	int t=strlen(str);
	int tc=strlen(strc);
	char * res = (char*) malloc(sizeof(char)*(t+tc));
	int i=0; 
	for(i=0; i<t; i++)
		res[i] = str [i];
	for(i=0; i<tc; i++)
		res[i+t] = strc [i];
	
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

char* saisie(){
	char c;
	char *res = "";
	while((c=getchar()) != '\n' && c != '\r' && c != EOF){
		res = concatene(res, c);
	}
	
	return res;
}
