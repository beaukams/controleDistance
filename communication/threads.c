#include <stdio.h>
#include <process.h>

int nb_thread = 0;
typedef struct{
	char* addr_serveur;
	int port_serveur;
}TClient;

void main(){

	//pour creer un thread serveur
	int port = 20019; 
	_beginthread(thread_server, 0, &port);
	
	//pour creer un thread client
	TClient cl;
	cl.addr_serveur = "127.0.0.1";
	cl.addr_port = 20019;
	_beginthread(thread_client, 0, &cl);
}


void thread_server(void *port_server){
	//****
	int port = (int) *port_server;
	//***le reste du code
}


void thread_client(void *port_server){
	//****
	int port = (int) *port_server;
	//***le reste du code
}