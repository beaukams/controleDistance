#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fichier = NULL;
char* ajouterUser();
int rechercheUser();
char *str_sub();
char* authentifierUser();


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
char* authentifierUser(char *login, char* pwd){
    fichier = fopen("fichierUser.txt", "r");
    char chaine[1000] = "";
    char* sortie;
   
    if (fichier != NULL)
    {
        while(fgets(chaine, 1000, fichier) != NULL){
			int pos=search(chaine,':');
			char* log=str_sub(chaine,0,pos-1);
			char* mdp=str_sub(chaine,pos+1,strlen(chaine));
			mdp=str_sub(mdp,0,search(mdp,':')-1);	
			if(strcmp(log, login)==0 && strcmp(mdp, pwd)==0){
			   sortie = "authentification etablie";
			}else{
				sortie = "login ou mot de passe incorrect";
			}
        }

        fclose(fichier);
    }
   return sortie;
}



//ajouter un utilisateur dans le fichier
char* ajouterUser(char* login, char* pwd, char* repUser){
	fichier = fopen("fichierUser.txt", "a+");
	char* sortie;
    if (fichier != NULL)
    {	
		if(rechercheUser(login)==0){
			fprintf(fichier, "%s:%s:%s \n",login,pwd,repUser);
			sortie= "utilisateur cree";
        }else{
			sortie= "Ce login existe deja";
		}
        fclose(fichier);
        
    }
    return sortie;
}

//rechercher si le login utilisateur existe ou pas
int rechercheUser(char* login){
	fichier = fopen("fichierUser.txt", "r");
	char chaine[1000] = "";
	char* verif;
	if (fichier != NULL)
    {
		while(fgets(chaine, 1000, fichier) != NULL){
			int pos=search(chaine, ':');
			verif= str_sub(chaine, 0, pos-1);
			if(strcmp(verif, login)==0){
				return 0;
			}
		}
		
		fclose(fichier);
    }
	return 1;
}

//extraire une chaine
char *str_sub (const char *s, unsigned int start, unsigned int end)
{
   char *new_s = NULL;
	if (s != NULL && start < end)
   {
      new_s = malloc (sizeof (*new_s) * (end - start + 2));
      if (new_s != NULL)
      {
         int i;
         for (i = start; i <= end; i++)
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

void listerUser(){
  fichier = fopen("fichierUser.txt", "r");
    char chaine[1000] = "";
    if (fichier == NULL)
    {
    printf("imosssible de lire le fichier");
  }
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

void supprimerUser(char*login){
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
      printf("imosssible d ecrire sur le fichier");
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
