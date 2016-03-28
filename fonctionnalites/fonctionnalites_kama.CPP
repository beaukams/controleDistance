#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <stddef.h>


/* API Fichier */
void creerFichier(char * path_file); //fait
int ouvrirFichier(char * path_file); //fait
int ouvrirFichierPourAction(char * path); //fait
char* lireFichier(char * path); //fait
int lireUnePartieFichier(char * path, char* data_to_read, int nb_read); //fait
int ecrireFichier(char *path, char* data);  //fait
void deplacerFichier(char * path_file); 
void copieFichier(char * path_file);
void supprimerFichier(char * path_file); //fait
void renommerFichier(char * ancien_filename,  char *nouveau_filename); //fait
void fermerFichier(char * path_file, int handle); //fait
int fermerFichierPourAction(char * path, int handle); //fait
int demanderAttribut(char * path_file);


/* API Dossier */
void creerDossier(char * path_rep); //fait 
void ouvrirDossier(char * path_rep); 
void supprimerDossier(char * path_rep); //fait
void renommerDossier(char * path_rep);
void copieDossier(char * path_rep);
void deplacerDossier(char * path_rep);
void fermerDossier(char * path_rep);
void dossierCourant(char * path_dir);
void changerDeDossier(char* path);

/* API Date et Heure */
void lireDate();


/* API Dessin */


/* API Reseaux */


/* fonctions de manipulations de la souris : interruption 33h*/

/* fonctions systemes : interruption 19h*/
void redemarrerSysteme();


/* fonctions de traitement */
char ** interpreteCommande(char * saisie);
int compteTermesCommande(char * saisie);
int longTab(char ** tab);
void ajouteCaractere(char* ch, char c);
char* charToChaine(char c);


/********************************* Programme principal ****************************/
void main(){
	clrscr();
	char * commande = (char*) malloc(100*sizeof(char));
	int handle;
	
	while(1){
		printf(">: ");
		//scanf("%s",commande);
		gets(commande);
		if(strcmp(commande,"mkdir")==0){
			//saisir dossier
			char* dossier;
			printf(">:saisir chemin du repertoire a creer: ");
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
			char* doss;
			dossierCourant(doss);
			printf(" %s \n",doss);
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
	getch();
	
}

/****************** fonctions de traitement ****************/
int compteTermesCommande(char * saisie){
	
	if(saisie==NULL)
		return 0;
		
	else{
	
		int res=1;
		int i=0; 
		
		for(i=0; i<strlen(saisie); i++){
			if(saisie[i]==' ')
				res++;
				
		}
		return res;
	}
}

int longTab(char ** tab){
	int res=0;
	for(res=0; res<10; res++)
		printf("%s ",tab[res]);
//	while(tab[res] != NULL){
	//	res++;
	//}
	getch();
	return res;
}

char ** interpreteCommande(char * chaine){
	/*int nb_termes = compteTermesCommande(saisie);
	char ** res = (char **) malloc(nb_termes*sizeof(char *));
	
	int numCaractere=0, numMot=0;
	char * temp="";
	
	int i=0;
	
	for(i=0; i<strlen(saisie); i++){
		printf("%c \n",saisie[i]);
		if(saisie[i]==' '){
			res[numMot] = temp;
			
			temp = "";
			numMot++;
		}
		else{
			char * car = &saisie[i];
			temp = strcat(temp,car);
		}
		
	}*/

	int i=0, j=0;
	
	int nb_mots = compteTermesCommande(chaine);


	char** tab =(char**) malloc(nb_mots*sizeof(char*));
	for(i=0; i<nb_mots; i++) 
		tab[i]=", sksk";//(char*) malloc(sizeof(char));
	
	for(i=0; i<strlen(chaine); i++){
		if(chaine[i]==' '){
			j++;
			//printf("%i\n",i);
		}else{
			ajouteCaractere(tab[j],chaine[i]);
		}
	}
	
	
	//for(i=0; i<j; i++) printf("%s --\n", tab[j]);
	//getch();
	
	return tab;

}

void ajouteCaractere(char* ch, char c){
	ch=(char*) realloc(ch,(strlen(ch)+2)*sizeof(char));
	*(ch+strlen(ch))=c;
	*(ch+strlen(ch)+1)='\0';

}
char* charToChaine(char c){
	char* res= (char*) malloc(2*sizeof(char));
	*(res+0)=c;
	*(res+1)='\0';
	return res;
}


/************************* fonctions de manipulations de repertoire ******************/

void creerDossier(char *path){
	disable();
	union REGS reg, oreg;
	struct SREGS sreg;
	reg.h.ah = 0x39;
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&reg,&sreg);

	if(reg.x.cflag==0){
		printf("Repertoire bien cree \n");
		getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==2){
			printf("Chemin introuvable\n");
			getch();
		}
		else if(reg.x.ax==5){
			printf("Pas de permissions\n");
			getch();
		}
		else{
			printf("NON GERE");
			getch();
		}
	}
	enable();
}



//supprimer un dossier: interruption 21h,
void supprimerDossier(char * path){
	union REGS reg, oreg; 
	struct SREGS sreg;
	reg.h.ah = 0x3a;
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&reg,&sreg);

	if(reg.x.cflag==0){
		printf("Sous-repertoire supprimé avec succès\n");
		getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==2){
			printf("Chemin introuvable\n");
			getch();
		}
		else if(reg.x.ax==5){
			printf("Pas de permissions\n");
			getch();
		}
		else{
			printf("Erreur de suppression");
			getch();
		}
	}
}

/* changer de repertoire courant */
void changerDeDossier(char* path){
	disable();
	union REGS reg; struct SREGS sreg;
	reg.h.ah = 0x3b;

	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment

	intdosx(&reg,&reg,&sreg);
	
	if(reg.x.cflag==0){
		printf("Cette valeur permet d'indiquer que le sous-répertoire a été changé avec succès\n");
		getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==2)
			printf("Chemin introuvable\n");
		else
			printf("Cas non pris en compte\n");
		
		getch();	
	}
	enable();
}


/* donner le dossier courant. Cette fonction permet demander le répertoire courant d'une unité de disque.*/
void dossierCourant(char * path){
	disable();
	union REGS reg; struct SREGS sreg;
	reg.h.ah = 0x47;
	reg.h.dl = 0; //unite de disque courante

	reg.x.si = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment

	intdosx(&reg,&reg,&sreg);
	
	if(reg.x.cflag==0){
		//printf("");
		//getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==15)
			printf("Unite de disque inconnue\n");
		getch();	
	}
	
	enable();
}

/************************** fonctions de manipulations de fichiers ********************/
void creerFichier(char * path){
	disable();
	union REGS reg; struct SREGS sreg;
	reg.h.ah = 0x3c;
	reg.x.cx = 0;//attribut du fichier
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&reg,&sreg);
	
	if(reg.x.cflag==0){
	//	printf("Fichier bien crée\n");
		//getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==3)
			printf("Chemin introuvable\n");
		else if(reg.x.ax==4)
			printf("il y a trop de fichiers ouverts simultanément\n");
		else if(reg.x.ax==5)
			printf("accès refusé\n");
		getch();	
	}
	enable();
}
/* ouvrir un fichier */
int ouvrirFichier(char * path){
	int handle=-1;
	
	disable();
	union REGS reg, oreg; struct SREGS sreg;
	reg.h.ah = 0x3d;
	//reg.h.al = 2; //fichier lu et ecrit 010
	//reg.h.al = reg.h.al|(3; //autre programme peut lire et écrit le fichier 011
	reg.h.al = 4*64+2;
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&oreg,&sreg);
	
	if(oreg.x.cflag==0){
	//	printf("ouverture du fichier a été un succès\n");
		handle=oreg.x.ax;
		//getch();
	}else if(oreg.x.cflag==1){
		if(oreg.x.ax==1)
			printf(" numéro de la fonction n'est pas valide et que vous n'avez pas de logiciel de partage de fichier\n");
		else if(oreg.x.ax==3)
			printf("chemin est introuvable\n");
		else if(oreg.x.ax==4)
			printf("il y a trop de fichiers ouverts simultanément\n");
		else if(oreg.x.ax==5)
			printf("accès refusé\n");
		else if(oreg.x.ax==12)
			printf("code d'accès est incorrecte\n");
		getch();	
	}
	enable();
	
	return handle;
}

int ouvrirFichierPourAction(char * path){
	int handle=-1;
	
	disable();
	union REGS reg, oreg; struct SREGS sreg;
	reg.h.ah = 0x3d;
	//reg.h.al = 2; //fichier lu et ecrit 010
	//reg.h.al = reg.h.al|(3; //autre programme peut lire et écrit le fichier 011
	reg.h.al = 4*64+2;
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&oreg,&sreg);
	
	if(oreg.x.cflag==0){
		handle=oreg.x.ax;
	//	getch();
	}
	
	enable();
	
	return handle;
}

/* lire tout le contenu d'un fichier */
char* lireFichier(char * path){
	char* chaine = "";
	int nb_read=0;
	int prec=0, temp=0;
	do{
		nb_read += 100;
		prec = temp;
		temp=lireUnePartieFichier(path, chaine, nb_read);
		
	}while(temp != prec);
	
	return chaine;
}

int lireUnePartieFichier(char * path, char* data_read, int nb_read){

	//ouvrir le fichier et recuperer le descripteur
	int handle = ouvrirFichierPourAction(path);
	
	int nb_data_read=0;
	
	disable();
	union REGS reg, oreg; struct SREGS sreg;
	reg.h.ah = 0x3f;
	reg.x.bx = handle; //descripteur du fichier
	reg.x.cx = nb_read; //nombre d'octets a ecrire
	reg.x.dx = FP_OFF(data_read); //adresse de l'offset
	sreg.ds = FP_SEG(data_read); //adresse du segment
	
	intdosx(&reg,&oreg,&sreg);
	
	if(oreg.x.cflag==0){
		//printf("L'ecriture du fichier a été un succès\n");
		nb_data_read = oreg.x.ax;
	//	getch();
	}else if(oreg.x.cflag==1){
		if(oreg.x.ax==6)
			printf("Handle est inconnu\n");
		else if(oreg.x.ax==5)
			printf("accès refusé\n");
		
		getch();	
	}
	
	enable();
	
	fermerFichierPourAction(path, handle);
	
	return nb_data_read;
}

//Cette fonction permet d'effectuer l'écriture dans un fichier en utilisant la méthode du Handle.
int ecrireFichier(char *path, char * data){
	int taille = strlen(data); //nombre de bytes des donnees
	
	//ouvrir le fichier et recuperer le descripteur
	int handle = ouvrirFichierPourAction(path);
	
	//nombre de bytes écrits avec succes
	int nb_data_write =0;
	
	disable();
	union REGS reg, oreg; struct SREGS sreg;
	
	reg.h.ah = 0x40;
	reg.x.bx = handle; //descripteur du fichier
	reg.x.cx = taille; //nombre d'octets a ecrire
	reg.x.dx = FP_OFF(data); //adresse de l'offset des donnees
	sreg.ds = FP_SEG(data); //adresse du segment des donnees
	
	intdosx(&reg,&oreg,&sreg);
	
	if(oreg.x.cflag==0){
	//	printf("L'ecriture du fichier s'est fait avec succès\n");
		nb_data_write = oreg.x.ax;
		//getch();
	}else if(oreg.x.cflag==1){
		if(oreg.x.ax==6)
			printf("Handle est inconnu\n");
		else if(oreg.x.ax==5)
			printf("accès refusé\n");
		
		getch();	
	}
	enable();
	
	//fermer le fichier
	fermerFichierPourAction(path, handle);
	
	return nb_data_write;
}

/* fermer un fichier ouvert */
void fermerFichier(char * path, int handle){
	disable();
	union REGS reg, oreg; struct SREGS sreg;
	reg.h.ah = 0x3e;
	
	reg.x.bx = handle; //descripteur du fichier
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&oreg,&sreg);
	
	if(oreg.x.cflag==0){
	}else if(oreg.x.cflag==1){
		if(oreg.x.ax==1)
			printf(" numéro de la fonction n'est pas valide et que vous n'avez pas de logiciel de partage de fichier\n");
		else if(oreg.x.ax==3)
			printf("chemin est introuvable\n");
		else if(oreg.x.ax==4)
			printf("il y a trop de fichiers ouverts simultanément\n");
		else if(oreg.x.ax==5)
			printf("accès refusé\n");
		else if(oreg.x.ax==12)
			printf("code d'accès est incorrecte\n");
		getch();	
	}
	enable();
}

void fermerFichierComplet(char * path, int handle){
	disable();
	union REGS reg, oreg; struct SREGS sreg;
	reg.h.ah = 0x3e;
	
	reg.x.bx = handle; //descripteur du fichier
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&oreg,&sreg);
	
	if(oreg.x.cflag==0){
		//printf("fermeture du fichier a été un succès\n");
		//getch();
	}else if(oreg.x.cflag==1){
		if(oreg.x.ax==1)
			printf(" numéro de la fonction n'est pas valide et que vous n'avez pas de logiciel de partage de fichier\n");
		else if(oreg.x.ax==3)
			printf("chemin est introuvable\n");
		else if(oreg.x.ax==4)
			printf("il y a trop de fichiers ouverts simultanément\n");
		else if(oreg.x.ax==5)
			printf("accès refusé\n");
		else if(oreg.x.ax==12)
			printf("code d'accès est incorrecte\n");
		getch();	
	}
	enable();
}


int fermerFichierPourAction(char * path, int handle){
	disable();
	union REGS reg, oreg; struct SREGS sreg;
	reg.h.ah = 0x3e;
	
	reg.x.bx = handle; //descripteur du fichier
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&oreg,&sreg);
	
	enable();

	return oreg.x.cflag;
}

void supprimerFichier(char * path){
	disable();
	union REGS reg; struct SREGS sreg;
	reg.h.ah = 0x41;
	reg.x.cx = 0;//attribut du fichier
	reg.x.dx = FP_OFF(path); //adresse de l'offset
	sreg.ds = FP_SEG(path); //adresse du segment
	intdosx(&reg,&reg,&sreg);
	
	if(reg.x.cflag==0){
		//printf("Fichier bien supprime\n");
		//getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==2)
			printf("Chemin introuvable\n");
		
		else if(reg.x.ax==5)
			printf("accès refusé\n");
		getch();	
	}
	enable();
}


/* renommer un fichier */
void renommerFichier(char * ancien_filename,  char *nouveau_filename){
	disable();
	union REGS reg; struct SREGS sreg;
	reg.h.ah = 0x56;
	

	//ancien fichier
	reg.x.dx = FP_OFF(ancien_filename); //adresse de l'offset 
	sreg.ds = FP_SEG(ancien_filename); //adresse du segment

	//nouveau nom de fichier
	reg.x.di = FP_OFF(nouveau_filename);
	sreg.es = FP_SEG(nouveau_filename);

	intdosx(&reg,&reg,&sreg);
	
	if(reg.x.cflag==0){
		//printf("Fichier bien deplacer\n");
		//getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==2)
			printf("Chemin introuvable\n");
		else if(reg.x.ax==3)
			printf("Chemin introuvable\n");
		else if(reg.x.ax==5)
			printf("accès refusé\n");
		else if(reg.x.ax==11)
			printf("format invalide\n");
		getch();	
	}
	enable();
}


/* copier un fichier */
void copieFichier(char* path_file, char* path_dossier){

	//lire le contenu du fichier
	char *contenu = lireFichier(path_file);
}


/* attributs d'un fichier */
int demanderAttribut(char * path_file){

	int res = -1;

	disable();
	union REGS reg; struct SREGS sreg;
	reg.h.ah = 0x4300;
	

	//ancien fichier
	reg.x.dx = FP_OFF(path_file); //adresse de l'offset 
	sreg.ds = FP_SEG(path_file); //adresse du segment

	intdosx(&reg,&reg,&sreg);
	
	if(reg.x.cflag==0){
		res = reg.x.cx;

		if(reg.x.cx & 1 == 1)
			printf("Mode lecture seulement\n");
		else
			printf("Mode lectur seulement\n");

		if(reg.x.cx & 2 == 1)
			printf("Fichier en mode caché\n");

		if(reg.x.cx & 4 == 1)
			printf("Fichier en mode systeme\n");

		if(reg.x.cx & 32 == 1)
			printf("Fichier en mode archivage\n");


		getch();
	}else if(reg.x.cflag==1){
		if(reg.x.ax==1)
			printf("fonction invalide\n");
		else if(reg.x.ax==2)
			printf("ficher introuvable\n");
		else if(reg.x.ax==3)
			printf("chemin introuvable\n");
		
		getch();	
	}
	enable();

	return res;
}


/********************** fonctions systemes **************************/


/*********************** fonctions de manipulations de la souris *****************/