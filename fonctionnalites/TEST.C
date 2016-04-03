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

        void main(int argc, char** argv){ 

        char *results = "";

	    clrscr(); 
	
	    
        if(argc>1){

        char* commande = argv[1];
        

		if(strcmp(commande,"mkdir")==0 && argc==3){ 

		results= creerDossier(argv[2]);

		}  

		else if(strcmp(commande,"rmdir")==0 && argc==3){ 


		results=supprimerDossier(argv[2]); 

		}

		else if(strcmp(commande,"cd")==0 && argc==3){ 

		results=changerDeDossier(argv[2]); 

		} 


		else if(strcmp(commande,"pwd")==0 && argc==3){ 


			dossierCourant(results); 


		}

		else if(strcmp(commande,"mkfile")==0 && argc==3){ 


			results=creerFichier(argv[2]); 


		}

		else if(strcmp(commande,"openfile")==0 && argc==3){ 
 

			results = ouvrirFichier(argv[2]); 


		}

		else if(strcmp(commande,"closefile")==0 && argc==3){ 

			results=fermerFichier(argv[2], handle); 


		} 

		else if(strcmp(commande,"rmfile")==0 && argc==3){ 

			results=supprimerFichier(argv[2]); 

		} 


		else if(strcmp(commande,"writefile")==0){ 

		if(argc>3){ 

			int i;

			for(i=3;i<argc; i++){
			
			results=ecrireFichier(argv[2],argv[i]);

			}
		}

		} 


		else if(strcmp(commande,"readfile")==0 && argc==3){ 


			results=lireFichier(argv[2]); 

		} 


		else if(strcmp(commande,"renamefile")==0 && argc==4){ 

			
			results=renommerFichier(argv[2], argv[3]); 

		} 

		else if(strcmp(commande,"masquagehorloge")==0 && argc==2){ 

			masquage();

		}


		else if(strcmp(commande,"getdate")==0 && argc==2){ 

			results=get_date();

		}

		else if(strcmp(commande,"setdate")==0 && argc==5){ 

			int jour= atoi(argv[2]);

			int moi= atoi(argv[3]);

			int annee=atoi(argv[4]);

			set_date(jour,moi,annee);
			
		    }  
		   


		else if(strcmp(commande,"exit")==0 && argc==2){ 

			results="Vous voulez quitter? Appuyer sur entree..."; 

		} 


		else if(strcmp(commande,"getheure")==0 && argc==2){ 

			results=get_heure();

		} 


		else if(strcmp(commande,"setheure")==0 && argc==5){

            int heure= atoi(argv[2]);

			int minute= atoi(argv[3]);

			int seconde=atoi(argv[4]);


			set_heure(heure,minute,seconde);

		} 
		
        
        else if(strcmp(commande,"disquecourant")==0 && argc==2){ 

			results=disquecourant();

		} 


		else if(strcmp(commande,"fdisk")==0 && argc==2){ 

			results=espacelibre();
		} 

		else if(strcmp(commande,"affichecouleure")==0 && argc==2){ 

			affichecouleure();

		} 

		else{
			results="Commande inconnu";
		}
		   
        } 

        }