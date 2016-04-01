#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct Personne{
		char login[10];
		char mdp[20];
		char rep[20];
} Personne;

FILE* fichier = NULL;
char* ajouterUser(const gchar* login, const gchar* pwd, const gchar* repUser);
int rechercheUser(const gchar* login);
int search (char *s, char carac);
void listerUser();
void supprimerUser(const gchar* login);
char *str_sub(const char *s, unsigned int start, unsigned int ends);
char* authentifierUser(const gchar *login,const gchar* pwd);



//extraire une chaine
char* str_sub(const char *s, unsigned int start, unsigned int ends)
{
    char *new_s = NULL;
    if (s != NULL && start < ends)
    {
        new_s = (char *)malloc (sizeof (*new_s) * (ends - start + 2));
        if (new_s != NULL)
        {
            int i;
            for (i = start; i <= ends; i++)
            {
                new_s[i-start] = s[i];
            }
            new_s[i-start] = '\0';
        }
        else
        {
            fprintf (stderr, "Memoire insuffisante\n");
            exit (EXIT_FAILURE);
        }
    }
    return new_s;
}
//trouver la position de la premiere occurrence d un caractere

int search (char *s, char carac)
{
    int i;
    for(i = 0; s[i] != '\0';i++)
        if(s[i] == carac)
            return i;
    return 0;
}


//verifier si l utilisateur existe (login, mot de passe)
char* authentifierUser(const gchar *login,const gchar* pwd)
{
    fichier = fopen("fichierUser.txt", "r");
    char chaine[1000] = "";
    char* sortie="";

    if (fichier != NULL)
    {
        while(fgets(chaine, 1000, fichier) != NULL)
        {
            int pos=search(chaine,':');
            char* log=str_sub(chaine,0,pos-1);
            char* c=str_sub(chaine,pos+1,strlen(chaine));
            char* mdp=str_sub(c,0,search(c,':')-1);
            char* repUser=str_sub(c,search(c,':')+1,strlen(c));
            if(strcmp(log, login)==0 && strcmp(mdp, pwd)==0)
            {
                sortie = repUser;
            }
            else
            {
                sortie = "";
            }
        }

        fclose(fichier);
    }
    return sortie;
}




//ajouter un utilisateur dans le fichier
char* ajouterUser(const gchar* login, const gchar* pwd, const gchar* repUser){
	fichier = fopen("fichierUser.txt", "a+");
	char* sortie="";
    if (fichier != NULL)
    {
		if(rechercheUser(login)==1){
			fprintf(fichier,"%s:%s:%s\n",login,pwd,repUser);
		    fclose(fichier);
			sortie= "Utilisateur cree\n";

        }else{
			sortie= "Ce login existe deja\n";
		}

    }
    else{
        printf("Le fichier na pu s'ouvrir ...\n");
    }
    return sortie;
}

Personne rechercheUser2(const gchar* login){
	fichier = fopen("fichierUser.txt", "r");
	char chaine[1000] = "";
	Personne pers;
	if (fichier != NULL)
    {
		while(fgets(chaine, 1000, fichier) != NULL){
			int pos=search(chaine,':');
			char* log=str_sub(chaine,0,pos-1);
			char* c=str_sub(chaine,pos+1,strlen(chaine));
			char* mdp=str_sub(c,0,search(c,':')-1);
			char* rep=str_sub(c,search(c,':')+1,strlen(c));
			if(strcmp(log, login)==0){
				strcpy(pers.login,log);
				strcpy(pers.mdp,mdp);
				strcpy(pers.rep,rep);
			}
		}

		fclose(fichier);
    }
	return pers;
}
//rechercher si le login utilisateur existe ou pas
int rechercheUser(const gchar* login){
	//fichier = fopen("fichierUser.txt", "r");
	char chaine[1000] = "";
	int trouve=1;
	char* verif;
	//if (fichier != NULL){
		while(fgets(chaine, 1000, fichier) != NULL){
			int pos=search(chaine, ':');
			verif= str_sub(chaine, 0, pos-1);
			if(strcmp(verif, login)==0){
                    trouve=0;
			}

		//}

		//fclose(fichier);
    }
	return trouve;
}

char* listerUser2(){
    fichier = fopen("fichierUser.txt", "r");
    char a[30000]="";
    char chaine[1000] = "";
    if (fichier != NULL){
         while(fgets(chaine, 1000, fichier) != NULL){
             strcat(a,chaine);
         }
    fclose(fichier);
    return a;
    }

    return a;

}

void listerUser(){
  fichier = fopen("fichierUser.txt", "r");
    char chaine[1000] = "";
    if (fichier != NULL)
    {
    printf("imposssible de lire le fichier");
  while(fgets(chaine, 1000, fichier) != NULL){
    int pos=search(chaine,':');
    char* log=str_sub(chaine,0,pos-1);
    char* c=str_sub(chaine,pos+1,strlen(chaine));
    char* mdp=str_sub(c,0,search(c,':')-1);
    char* rep=str_sub(c,search(c,':')+1,strlen(c));
    printf("login:%s mot de passe:%s répertoire:%s \n",log,mdp,rep);
  }
   fclose(fichier);
  }
  else{
    printf("Fichier Error");
  }
}

void supprimerUser(const gchar* login){
  fichier = fopen("fichierUser.txt", "r");
  char chaine[1000] = "";
  FILE* copiefichier = NULL;
  copiefichier = fopen("copieFichier.txt", "w");
    if (fichier == NULL)
    {
      printf("imosssible de lire le fichier");
  }
  if (copiefichier == NULL)
    {
      printf("impossible d ecrire sur le fichier");
  }
  while(fgets(chaine, 1000, fichier) != NULL){
    int pos=search(chaine,':');
    char* log=str_sub(chaine,0,pos-1);
    if(strcmp(log, login)!=0){
       fputs(chaine, copiefichier);
    }
  }

  fclose(fichier);
  fclose(copiefichier);
  remove("fichierUser.txt");
  rename("copieFichier.txt","fichierUser.txt");
}
