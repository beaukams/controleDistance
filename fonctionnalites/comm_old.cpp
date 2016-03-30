#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <stddef.h>

char * interprete_commande(char * chaine);
char ** prompt();


/********************************* Programme principal ****************************/
void main(int argc, char** argv){
	clrscr();
	char * commande = argv;
	int handle;
	
	printf(">: ");
	gets(commande);
		
	
}

char ** init_prompt(){
	char* prompt;
	return 
}

char * interprete_commande(int argc, char** argv){
	char *results;
	if(strcmp(commande,"mkdir")==0){
			char* dossier;
			gets(dossier);
			creerDossier(dossier);
		}else if(strcmp(commande,"rmdir")==0){
			//saisir dossier
			char* dossier;
			printf(">:saisir chemin du repertoire a supprimer: ");
			gets(dossier);
			supprimerDossier(dossier);
		}else if(strcmp(commande,"cd")==0){
			//saisir dossier
			char* dossier;
			printf(">:saisir le repertoire ou vous voulez allez");
			gets(dossier);
			changerDeDossier(dossier);
		}else if(strcmp(commande,"pwd")==0){
			dossierCourant(results);

		}else if(strcmp(commande,"mkfile")==0){
			char* fichier;
			printf(">:saisir chemin du fichier a creer: ");
			gets(fichier);
			creerFichier(fichier);
		}else if(strcmp(commande,"openfile")==0){
			char* fichier;
			printf(">:saisir chemin du fichier a ouvrir: ");
			gets(fichier);
			handle = ouvrirFichier(fichier);
		}else if(strcmp(commande,"closefile")==0){
			char* fichier;
			printf(">:saisir chemin du fichier a fermer: ");
			gets(fichier);
			fermerFichier(fichier, handle);
		}else if(strcmp(commande,"rmfile")==0){
			char* fichier;
			printf(">:saisir chemin du fichier a supprimer: ");
			gets(fichier);
			supprimerFichier(fichier);
		}else if(strcmp(commande,"writefile")==0){
			char* fichier;
			char* data;
			
			printf(">:saisir chemin du fichier sur le quel ecrire: ");
			gets(fichier);
			
			printf(">:saisir le texte: ");
			gets(data);
			
			ecrireFichier(fichier,data);
			
		}else if(strcmp(commande,"readfile")==0){
			char* fichier;
			
			printf(">:saisir chemin du fichier a lire: ");
			gets(fichier);
			printf("%s\n",lireFichier(fichier));
		}else if(strcmp(commande,"renamefile")==0){
			char*  source;
			char * dest;
			printf(">:saisir chemin du fichier a renommer ou deplacer: ");
			gets(source);
			printf(">:saisir le nouveau du fichier ");
			gets(dest);
			renommerFichier(source, dest);
		}else if(strcmp(commande,"showmod")==0){
			char*  fichier;
			printf(">:saisir chemin du fichier ");
			gets(fichier);
			demanderAttribut(fichier);
		}else if(strcmp(commande,"exit")==0){
			printf(">:Vous voulez quitter? Appuyer sur entree...");
			break;
		}
		else{
			printf(">:Commande inconnue\n");
		}

}