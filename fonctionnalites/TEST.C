      #include <stdio.h> 

      #include <stdlib.h>

      #include <conio.h>

      #include <string.h> 

      #include <dos.h> 

      #include <stddef.h> 

      #include <fonction.h> 


/*

la liste des commandes sont:

masquagehorloge pour masquer les interruptions de l'horloge

mkdir pour creer un repertoire

rmdir pour supprimer un repertoire

cd pour se positionner sur un repertoire

pwd pour connaitre son repertoire courant

mkfile pour creer un fichier

openfile pour ouvrir un fichier

closefile pour fermer un fichier

rmfile pour supprimer un fichier

writefile pour ecrire dans un fichier

readfile pour lire dans un fichier

renamefile pour renommer un fichier

getdate pour obtenir la date

setdate pour mettre a jour la date

getheure pour obtenir l'heure du systeme

setheure pour mettre a jour l'heure

fdisk pour avoir les infos sur les drives du disque

disquecourant pour connaitre son disque courant

affichecouleure pour passer en mode graphique

*/

        int handle;

        void main(){ 

        char * commande = (char*) malloc(100*sizeof(char)); 

	    clrscr(); 
	
	    while(1){ 

		 printf(">: "); 

		scanf("%s",commande);

		if(strcmp(commande,"mkdir")==0){ 

			//saisir dossier 

			char* dossier; 

			printf(">:saisir chemin du repertoire a creer: "); 

			scanf("%s",dossier);

			creerDossier(dossier);

		}  


		else if(strcmp(commande,"rmdir")==0){ 

			//saisir dossier 

			char* dossier; 

			printf(">:saisir chemin du repertoire a supprimer: "); 

			scanf("%s", dossier);

			supprimerDossier(dossier); 

		}

		else if(strcmp(commande,"cd")==0){ 

			//saisir dossier
			char* dossier; 

			printf(">:saisir le repertoire ou vous voulez allez"); 

			scanf("%s",dossier);

			changerDeDossier(dossier); 


		}

		else if(strcmp(commande,"pwd")==0){ 

			char* doss; 

			dossierCourant(doss); 

			printf(" %s \n",doss); 


		}

		else if(strcmp(commande,"mkfile")==0){ 

			char* fichier;

			printf(">:saisir chemin du fichier a creer: ");

			scanf("%s",fichier);

			creerFichier(fichier); 


		}

		else if(strcmp(commande,"openfile")==0){ 

			char* fichier; 

			printf(">:saisir chemin du fichier a ouvrir: "); 

			scanf("%s",fichier); 

			handle = ouvrirFichier(fichier); 


		}

		else if(strcmp(commande,"closefile")==0){ 

			char* fichier; 

			printf(">:saisir chemin du fichier a fermer: "); 

			scanf("%s",fichier); 

			fermerFichier(fichier, handle); 


		} 

		else if(strcmp(commande,"rmfile")==0){ 

			char* fichier; 

			printf(">:saisir chemin du fichier a supprimer: "); 

			scanf("%s",fichier);

			supprimerFichier(fichier); 

		} 


		else if(strcmp(commande,"writefile")==0){  

			char* fichier; 

			char* data;
			
			printf(">:saisir chemin du fichier sur le quel ecrire: "); 

			scanf("%s",fichier);
			
			printf(">:saisir le texte: "); 

			scanf("%s",data);
			
			ecrireFichier(fichier,data);

		} 


		else if(strcmp(commande,"readfile")==0){ 

			char* fichier;
			
			printf(">:saisir chemin du fichier a lire: "); 

			scanf("%s",fichier); 

			printf("%s\n",lireFichier(fichier)); 

		} 


		else if(strcmp(commande,"renamefile")==0){ 

			char*  source; 

			char * dest; 

			printf(">:saisir chemin du fichier a renommer ou deplacer: "); 

			scanf("%s",source); 

			printf(">:saisir le nouveau du fichier "); 

			scanf("%s",dest); 

			renommerFichier(source, dest); 

		} 

		else if(strcmp(commande,"masquagehorloge")==0){ 

			masquage();

		}


		else if(strcmp(commande,"getdate")==0){ 

			get_date();

		}

		else if(strcmp(commande,"setdate")==0){ 

			int jour, mois, annee, c; 

			printf(">:saisir le Jour "); 

			scanf("%d",&jour);

			printf(">:saisir le Mois ");  

			scanf("%d",&mois);

			printf(">:saisir Annee ");  

			scanf("%d",&annee);

			c= set_date(jour,mois,annee);

			if(c==0){ 

				printf(" la date est mise a jour\n");
			}

			else{
				printf(" la mise a jour de la date a echouee\n");
			}


		    }  

		else if(strcmp(commande,"exit")==0){ 

			printf(">:Vous voulez quitter? Appuyer sur entree..."); 

			break;
		} 


		else if(strcmp(commande,"getheure")==0){ 

			get_heure();

			printf("\n");

		} 


		else if(strcmp(commande,"setheure")==0){ 

			int heure, minute, secondes, e;

            printf(">:saisir Heure "); 

			scanf("%d",&heure);

			printf(">:saisir Minute ");  

			scanf("%d",&minute);

			printf(">:saisir Secondes ");  

			scanf("%d",&secondes);

			 e= set_heure(heure, minute, secondes);

			 if(e==0){ 

				printf(" heure mise a jour\n");
			}

			else{
				printf(" la mise a jour de heure a echouee\n");
			}

		} 
        
        else if(strcmp(commande,"disquecourant")==0){ 

			disquecourant();

			printf("\n");

		} 


		else if(strcmp(commande,"fdisk")==0){ 

			espacelibre();


		} 

		else if(strcmp(commande,"affichecouleure")==0){ 

			affichecouleure();

		} 
        
        else if(strcmp(commande,"affichesouris")==0){ 

			affichesouris();

		} 
		   else { 

		   printf(">:Commande inconnue \n");

		   } 
		   

           } 

           getch();

           }