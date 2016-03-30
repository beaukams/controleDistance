
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

FILE* fichier = NULL;
char* ajouterUser();
int rechercheUser(char* login);
char *str_sub(const char *s, unsigned int start, unsigned int ends);
int authentifierUser();


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
char* authentifierUser(const gchar *login,const gchar* pwd){
    fichier = fopen("fichierUser.txt", "r");
    char chaine[1000] = "";
    char* sortie;

    if (fichier != NULL)
    {
        while(fgets(chaine, 1000, fichier) != NULL){
			int pos=search(chaine,':');
			char* log=str_sub(chaine,0,pos-1);
			char* c=str_sub(chaine,pos+1,strlen(chaine));
			char* mdp=str_sub(c,0,search(c,':')-1);
			char* repUser=str_sub(c,search(c,':')+1,strlen(c));
			if(strcmp(log, login)==0 && strcmp(mdp, pwd)==0){
			   sortie = repUser;
			}else{
				sortie = "";
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

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;


    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char**)malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
