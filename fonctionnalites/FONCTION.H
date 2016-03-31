
#include<stdio.h>
#include<dos.h>
#include<conio.h> 

unsigned int offs, seg;
union REGS ur;
union REGS urOut;
struct SREGS sr;

union REGS reg, oreg;
struct SREGS sreg; 



// fonction de creation d'un dossier 

void creerDossier(char *path){ 

    disable();
    
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

void dossierCourant(char * path){
    disable();
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


void creerFichier(char * path){
    disable();
    reg.h.ah = 0x3c;
    reg.x.cx = 0;//attribut du fichier
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment
    intdosx(&reg,&reg,&sreg);
    
    if(reg.x.cflag==0){
    //  printf("Fichier bien crée\n");
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

int ouvrirFichier(char * path){
    int handle=-1;
    
    disable(); 

    reg.h.ah = 0x3d;
    //reg.h.al = 2; //fichier lu et ecrit 010
    //reg.h.al = reg.h.al|(3; //autre programme peut lire et écrit le fichier 011
    reg.h.al = 4*64+2;
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment
    intdosx(&reg,&oreg,&sreg);
    
    if(oreg.x.cflag==0){
    //  printf("ouverture du fichier a été un succès\n");
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

void fermerFichier(char * path, int handle){
    disable();
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


void supprimerFichier(char * path){
    disable();
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

int ecrireFichier(char *path, char * data){
    int taille = strlen(data); //nombre de bytes des donnees
    
    //ouvrir le fichier et recuperer le descripteur
    int handle = ouvrirFichierPourAction(path);
    
    //nombre de bytes écrits avec succes
    int nb_data_write =0;
    
    disable();
    
    reg.h.ah = 0x40;
    reg.x.bx = handle; //descripteur du fichier
    reg.x.cx = taille; //nombre d'octets a ecrire
    reg.x.dx = FP_OFF(data); //adresse de l'offset des donnees
    sreg.ds = FP_SEG(data); //adresse du segment des donnees
    
    intdosx(&reg,&oreg,&sreg);
    
    if(oreg.x.cflag==0){
    //  printf("L'ecriture du fichier s'est fait avec succès\n");
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


void renommerFichier(char * ancien_filename,  char *nouveau_filename){
    disable();
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


int demanderAttribut(char * path_file){

    int res = -1;

    disable();
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


int lireUnePartieFichier(char * path, char* data_read, int nb_read){

    //ouvrir le fichier et recuperer le descripteur
    int handle = ouvrirFichierPourAction(path);
    
    int nb_data_read=0;
    
    disable();
    reg.h.ah = 0x3f;
    reg.x.bx = handle; //descripteur du fichier
    reg.x.cx = nb_read; //nombre d'octets a ecrire
    reg.x.dx = FP_OFF(data_read); //adresse de l'offset
    sreg.ds = FP_SEG(data_read); //adresse du segment
    
    intdosx(&reg,&oreg,&sreg);
    
    if(oreg.x.cflag==0){
        //printf("L'ecriture du fichier a été un succès\n");
        nb_data_read = oreg.x.ax;
    //  getch();
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

int fermerFichierPourAction(char * path, int handle){
    disable();
    reg.h.ah = 0x3e;
    
    reg.x.bx = handle; //descripteur du fichier
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment
    intdosx(&reg,&oreg,&sreg);
    
    enable();

    return oreg.x.cflag;
} 

int ouvrirFichierPourAction(char * path){
    int handle=-1;
    
    disable();
    reg.h.ah = 0x3d;
    //reg.h.al = 2; //fichier lu et ecrit 010
    //reg.h.al = reg.h.al|(3; //autre programme peut lire et écrit le fichier 011
    reg.h.al = 4*64+2;
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment
    intdosx(&reg,&oreg,&sreg);
    
    if(oreg.x.cflag==0){
        handle=oreg.x.ax;
    //  getch();
    }
    
    enable();
    
    return handle;
}



void get_date(){
    ur.h.ah = 0x2A;
    int86(0x21,&ur,&urOut);

    printf("Date du jour : %d \/ %d \/ %d \n", _DL, _DH, _CX);
}

//fonction permettant de mettre à jour la date su système
const int set_date(unsigned int jour, unsigned int mois, unsigned int annee){
    ur.h.ah = 0x2B;
    ur.x.cx = annee;
    ur.h.dh = mois;
    ur.h.dl = jour;
    
    int86(0x21, &ur, &urOut);

    return ur.h.al;
}


//fonction permettant d'afficher l'heure du systeme
void get_heure(){
    ur.h.ah = 0x2C;
    int86(0x21,&ur,&urOut);

    printf("\nHeure : %d: %d: %d", _CH, _CL, _DH);
} 


//fonction permettant de mettre à jour l'heure su système
const int set_heure(unsigned int h, unsigned int mn, unsigned int secondes){
    ur.h.ah = 0x2D;
    ur.h.dh = secondes;
    ur.h.cl = mn;
    ur.h.ch = h;
    int86(0x21, &ur, &urOut);

    return ur.h.al;
} 

const int espacelibre(){
    ur.h.ah = 0x36;
    ur.h.dl = 0;//le numero du volume de disque

    int86(021, &ur, &urOut);
    
    printf("\n%d", ur.x.ax);
    printf("\n%d", ur.x.bx);
    printf("\n%d", ur.x.cx);
    printf("\n%d", ur.x.dx);
    
    return ur.x.ax * ur.x.bx * ur.x.cx;
}


//fonction permettant de retourner l espace total du disque
const int espacetotal(){
    ur.h.ah = 0x36;
    ur.h.dl = 0;//le numero du volume de disque

    int86(021, &ur, &urOut);
    
    printf("\n%d", ur.x.ax);
    printf("\n%d", ur.x.bx);
    printf("\n%d", ur.x.cx);
    printf("\n%d", ur.x.dx);
    
    return ur.x.ax * ur.x.cx * ur.x.dx;
}