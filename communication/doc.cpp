//SERVEUR: 
 
#include <stdlib.h> 
#include <stdio.h>   
#include <dos.h>   
#include <conio.h>   
#include <winsock2.h> 
#pragma comment(lib, "ws2_32.lib" ) 
 
int main() 
{  
 WSADATA WSAData; 
 WSAStartup(MAKEWORD(2,0), &WSAData); 
  
 SOCKET sock; 
 SOCKADDR_IN sin; 
 SOCKADDR_IN csin; 
  
 sock = socket(AF_INET, SOCK_STREAM, 0); 
 sin.sin_addr.s_addr = INADDR_ANY; 
 sin.sin_family     = AF_INET; 
 sin.sin_port     = htons(4444); 
 
        bind(sock, (SOCKADDR *)&sin, sizeof(sin)); 
 listen(sock, 0); 
        printf("Attente d'une connection...\n" ); 
 int sinsize = sizeof(csin); 
  
 sock = accept(sock, (SOCKADDR *)&csin, &sinsize); 
 printf("connection etablie\n\n" ); 
 u_long argp=1;     /*mode non bloquant*/ 
 ioctlsocket(sock, FIONBIO, &argp); 
 
 do 
 { 
  
/*dialogue entre les untilisateurs avec "recv()" et "send()" */ 
 
 bind(sock, (SOCKADDR *)&sin, sizeof(sin)); 
 listen(sock, 0); 
 int sinsize = sizeof(csin); 
   
 sock = accept(sock, (SOCKADDR *)&csin, &sinsize); 
 printf("OK" ); /*J'ai ajouté ca dans la boucle pour rendre le serveur dispo nimporte quant*/ 
 
 Sleep(10);/*pour pas bloquer le CPU*/ 
 }while(!quit); 
 
//CLIENT :Je le lance 2 fois ce prog pour avoir 3personnes connectés  
//(2 Clients + 1 Serveur) 
 
#include <stdlib.h> 
#include <stdio.h>     
#include <conio.h>  
#include <dos.h> 
#include <winsock2.h> 
#pragma comment (lib,"ws2_32.lib" ) 
 
int main() 
{ 
 WSADATA WSAData; 
 WSAStartup(MAKEWORD(2,0), &WSAData); 
 
 SOCKET sock; 
 SOCKADDR_IN sin; 
 char ip[16]; 
 
 textcolor(10); 
 cprintf("Entrer l'adresse IP du serveur\r\n" ); 
 gets(ip); 
  
 sock = socket(AF_INET, SOCK_STREAM, 0); 
 sin.sin_addr.s_addr = inet_addr(ip); 
 sin.sin_family     = AF_INET; 
 sin.sin_port     = htons(4444); 
 
 connect(sock, (SOCKADDR *)&sin, sizeof(sin)); 
 u_long argp=1; /* pour passer en mode non bloquant */ 
 ioctlsocket(sock, FIONBIO, &argp); 
 
 	do 
 	{ 
 
 /*dialogue entre les untilisateurs avec "recv()" et "send()" */ 
 	Sleep(10);/*pour pas bloquer le CPU*/ 
 	}while(!quit); 
  
 closesocket(sock);/*fermeture*/ 
 WSACleanup(); 
 return(0); 
} 
 