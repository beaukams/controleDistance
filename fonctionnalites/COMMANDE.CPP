#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <stddef.h>
#include "FONCTIONNALITES.CPP"

void interprete_commande(int argc, char** argv);



/********************************* Programme principal ****************************/
void main(int argc, char** argv){
	clrscr();
	
	interprete_commande(argc, argv);
}



void interprete_commande(int argc, char** argv){
	char *results = ""; //resultat de la commande
	int handle;

	if(argc>1){
		char* commande = argc[1];

		if(strcmp(commande, pwd)=0 && argc=2){
			dossierCourant(results);
		}else if(strcmp(commande, cd)=0 && argc=3){
			changerDeDossier(argv[2], &results);
		}else{
			results = "Commande inconnue";
		}
	}else{ //on renvoie seulement le prompt
		results = dossierCourant(results);
	}

	//stcoker la chaine dans le fichier
	
}