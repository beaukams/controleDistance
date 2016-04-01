
#include<stdio.h>
#include<dos.h>
#include<conio.h> 
#include<graphics.h>
#include<time.h>

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
        printf("Sous-repertoire supprime avec succes\n");
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


void demanderAttribut(char * path_file){

    int res = -1;

    disable(); 

    reg.h.ah = 0x4300;
    
    printf(" la tete est");

    //ancien fichier
    reg.x.dx = FP_OFF(path_file); //adresse de l'offset 
    sreg.ds = FP_SEG(path_file); //adresse du segment

    intdosx(&reg,&reg,&sreg);
    
    if(reg.x.cflag==0){
        res = reg.x.cx;

        if(reg.x.cx == 1)
            printf("Mode lecture seulement\n");

        if(reg.x.cx == 2)
            printf("Fichier en mode caché\n");

        if(reg.x.cx == 4)
            printf("Fichier en mode systeme\n");

        if(reg.x.cx == 32)
            printf("Fichier en mode archivage\n");


        getch(); 

    }
    else if(reg.x.cflag==1){ 

        if(reg.x.ax==1)
            printf("fonction invalide\n");
        else if(reg.x.ax==2)
            printf("ficher introuvable\n");
        else if(reg.x.ax==3)
            printf("chemin introuvable\n");
        
        getch(); 

    } 

    enable();
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
    ur.h.ch = h;
    ur.h.cl = mn;
    ur.h.dh = secondes; 

    int86(0x21, &ur, &urOut); 

    return ur.h.al;
} 

void espacelibre(){
    ur.h.ah = 0x36;
    ur.h.dl = 3;//le numero du volume de disque

    int86(021, &ur, &urOut);
    
    printf("Nombre de secteur par cluster %d\n", ur.x.ax);
    printf("Nombre de cluster encore libre %d\n", ur.x.bx);
    printf("Nombre d'octect par secteurs %d\n", ur.x.cx);
    printf("Nombre de clusters sur l'unite %d\n", ur.x.dx);
    
} 

void disquecourant(){

    ur.h.ah = 0x19;

    int86(021, &ur, &urOut);

    printf("le numero du disque courant est %d", ur.h.al );
} 


void affichecurseur(){

ur.h.ah = 0x1;

ur.h.ch = 0x50;

ur.h.cl= 0x50;

int86(010, &ur, &urOut);

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



void affichePixel(unsigned x, unsigned y, char couleur){
 char far *vga =(char far *)MK_FP(0xA000,0x0000);
   *(vga + x + 320*y) = couleur;
}


int affichecouleure()
{   
     union REGS r_inreg;

    int i=0,j=0,k=128;

    _AX = 0x0013; 

    geninterrupt(0x10);
    for (k =0 ; k < 255; k+=10)
    {
        for (i = 0; i <= 320; i++)
        {
            for(j = 0; j < 200; j++)
            {   
                affichePixel(i,j,k);
            }
        }
        _AX=0x0003;
    //  geninterrupt(0x10);
        sleep(1);
    }
    return 0;
}
 


void initialiser(){ 

    ur.x.ax = 0;

    int86(033, &ur, &urOut);

}

void affichesouris(){

    ur.x.ax = 7;

    ur.x.cx = 50;

    ur.x.dx = 50;

    int86(0x33, &ur, &urOut);
} 


int masquage() { 

int res,cur,count=0;
    clrscr();
    res = inport(0x21);
    printf("%2x\n",res);
    while(count <= 15){

        if (count == 5){

            printf("\n Debut du blocage \n");
            //cur = res & 0x00;
            outport(0x21,res | 0x01);
        }
        else
            if (count == 10){

                printf("\n Fin du blocage \n");
                outport(0x21,res);
            }

        printf("\n nbr interrupt = %d",clock());
        delay(1000);
        count++;
        if (count==16){
            printf("\n");
            getch();
        }
    }
    return 0;
}