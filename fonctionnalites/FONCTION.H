
#include<stdio.h>
#include<dos.h>
#include<conio.h> 
#include<graphics.h>
#include<string.h>
#include<time.h>

unsigned int offs, seg;
union REGS ur;
union REGS urOut;
struct SREGS sr;

union REGS reg, oreg;
struct SREGS sreg; 



// fonction de creation d'un dossier 

char * creerDossier(char *path){ 
    char *mes="";
    disable();
    
    reg.h.ah = 0x39;
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment
    intdosx(&reg,&reg,&sreg);

    if(reg.x.cflag==0){ 
        mes= "Repertoire bien cree";
    }else if(reg.x.cflag==1){
        if(reg.x.ax==2){
            mes="Chemin introuvable";
        }
        else if(reg.x.ax==5){
            mes="Pas de permissions";
        }
        else{
            mes= "NON GERE";
        }
    }
    enable();

    return mes;
} 

char * supprimerDossier(char * path){
    char *mes="";
    union REGS reg, oreg; 
    struct SREGS sreg;
    reg.h.ah = 0x3a;
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment
    intdosx(&reg,&reg,&sreg);

    if(reg.x.cflag==0){
        mes="Sous-repertoire supprime avec succes";
        
    }else if(reg.x.cflag==1){
        if(reg.x.ax==2){
            mes="Chemin introuvable";
        }
        else if(reg.x.ax==5){
            mes="Pas de permissions";
        }
        else{
            mes="Erreur de suppression";
        }
    }
    return mes;
}

/* changer de repertoire courant */
char * changerDeDossier(char* path){
    char *mes="";
    disable();
    reg.h.ah = 0x3b;
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment

    intdosx(&reg,&reg,&sreg);
    
    if(reg.x.cflag==0){
        mes="Cette valeur permet d'indiquer que le sous-répertoire a été changé avec succès";
        
    }else if(reg.x.cflag==1){
        if(reg.x.ax==2)
            mes="Chemin introuvable";
        else
            mes="Cas non pris en compte";    
    }
    enable();
    return mes;
}

char * dossierCourant(char * path){
    char *mes="";
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
            mes="Unite de disque inconnue";   
    }
    
    enable();
    return mes;
}


char* creerFichier(char * path){
    char *mes="";
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
            mes="Chemin introuvable";
        else if(reg.x.ax==4)
            mes="il y a trop de fichiers ouverts simultanément";
        else if(reg.x.ax==5)
            mes="accès refusé";    
    }
    enable();

    return mes;
}

char * ouvrirFichier(char * path){
    char * mes="";
    
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
        //getch();
    }else if(oreg.x.cflag==1){
        if(oreg.x.ax==1)
            mes="numéro de la fonction n'est pas valide et que vous n'avez pas de logiciel de partage de fichier";
        else if(oreg.x.ax==3)
            mes="chemin est introuvable";
        else if(oreg.x.ax==4)
            mes="il y a trop de fichiers ouverts simultanément";
        else if(oreg.x.ax==5)
            mes="accès refusé";
        else if(oreg.x.ax==12)
            mes="code d'accès est incorrecte";   
    }
    enable();
    
    return mes;
}

char* fermerFichier(char * path, int handle){
    char *mes="";
    disable();
    reg.h.ah = 0x3e;
    
    reg.x.bx = handle; //descripteur du fichier
    reg.x.dx = FP_OFF(path); //adresse de l'offset
    sreg.ds = FP_SEG(path); //adresse du segment
    intdosx(&reg,&oreg,&sreg);
    
    if(oreg.x.cflag==0){
    }else if(oreg.x.cflag==1){
        if(oreg.x.ax==1)
            mes=" numéro de la fonction n'est pas valide et que vous n'avez pas de logiciel de partage de fichier";
        else if(oreg.x.ax==3)
            mes="chemin est introuvable";
        else if(oreg.x.ax==4)
            mes="il y a trop de fichiers ouverts simultanément";
        else if(oreg.x.ax==5)
            mes="accès refusé";
        else if(oreg.x.ax==12)
            mes="code d'accès est incorrecte";   
    }
    enable();
    return mes;
}


char* supprimerFichier(char * path){
    char *mes="";
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
            mes="Chemin introuvable";
        
        else if(reg.x.ax==5)
            mes="accès refusé";    
    }
    enable();
    return mes;
} 

char * ecrireFichier(char *path, char * data){

    char * mes="";

    int taille = strlen(data); //nombre de bytes des donnees
    
    //ouvrir le fichier et recuperer le descripteur
    int handle = ouvrirFichierPourAction(path);
    
    //nombre de bytes écrits avec succes
    
    disable();
    
    reg.h.ah = 0x40;
    reg.x.bx = handle; //descripteur du fichier
    reg.x.cx = taille; //nombre d'octets a ecrire
    reg.x.dx = FP_OFF(data); //adresse de l'offset des donnees
    sreg.ds = FP_SEG(data); //adresse du segment des donnees
    
    intdosx(&reg,&oreg,&sreg);
    
    if(oreg.x.cflag==0){
    //  printf("L'ecriture du fichier s'est fait avec succès\n");
        //getch();
    }else if(oreg.x.cflag==1){
        if(oreg.x.ax==6)
            mes="Handle est inconnu";
        else if(oreg.x.ax==5)
            mes="accès refusé";
          
    }
    enable();
    
    //fermer le fichier
    fermerFichierPourAction(path, handle);
    
    return mes;
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


char* renommerFichier(char * ancien_filename,  char *nouveau_filename){
    char *mes="";
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
            mes="Chemin introuvable";
        else if(reg.x.ax==3)
            mes="Chemin introuvable";
        else if(reg.x.ax==5)
            mes="accès refusé";
        else if(reg.x.ax==11)
            mes="format invalide";    
    }
    enable();
    return mes;
}


char * demanderAttribut(char * path_file){

    char * mes="";

    disable(); 

    reg.h.ah = 0x4300;
    
    printf(" la tete est");

    //ancien fichier
    reg.x.dx = FP_OFF(path_file); //adresse de l'offset 
    sreg.ds = FP_SEG(path_file); //adresse du segment

    intdosx(&reg,&reg,&sreg);
    
    if(reg.x.cflag==0){

        if(reg.x.cx == 1)
            mes="Mode lecture seulement";

        if(reg.x.cx == 2)
            mes="Fichier en mode caché";

        if(reg.x.cx == 4)
            mes="Fichier en mode systeme";

        if(reg.x.cx == 32)
            mes="Fichier en mode archivage";

    }
    else if(reg.x.cflag==1){ 

        if(reg.x.ax==1)
            mes="fonction invalide";
        else if(reg.x.ax==2)
            mes="ficher introuvable";
        else if(reg.x.ax==3)
            mes="chemin introuvable";

    } 

    enable();

    return mes;
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



   char *get_date(){ 

    char* mes[3];
    ur.h.ah = 0x2A;
    int86(0x21,&ur,&urOut);

   // printf("Date du jour : %d \/ %d \/ %d \n", _DL, _DH, _CX);

    mes[0]=(char*)_DL;
    mes[1]=(char*)_DH;
    mes[2]=(char*)_CX;

     return *mes;
}

//fonction permettant de mettre à jour la date su système
void set_date(unsigned int jour, unsigned int mois, unsigned int annee){
    ur.h.ah = 0x2B;
    ur.x.cx = annee;
    ur.h.dh = mois;
    ur.h.dl = jour;
    
    int86(0x21, &ur, &urOut);

}



//fonction permettant d'afficher l'heure du systeme
char * get_heure(){ 


    char* mes[3];

    ur.h.ah = 0x2C;

    int86(0x21,&ur,&urOut);

    mes[0]=(char*)_CH;
    mes[1]=(char*)_CL;
    mes[2]=(char*)_DH;

    return *mes;
} 


//fonction permettant de mettre à jour l'heure su système

void set_heure(unsigned int h, unsigned int mn, unsigned int secondes){
    ur.h.ah = 0x2D;
    ur.h.ch = h;
    ur.h.cl = mn;
    ur.h.dh = secondes; 

    int86(0x21, &ur, &urOut); 

} 

char * espacelibre(){
    char * mes[4];
    ur.h.ah = 0x36;
    ur.h.dl = 3;//le numero du volume de disque

    int86(021, &ur, &urOut);

    /*
    
    printf("Nombre de secteur par cluster %d\n", ur.x.ax);
    printf("Nombre de cluster encore libre %d\n", ur.x.bx);
    printf("Nombre d'octect par secteurs %d\n", ur.x.cx);
    printf("Nombre de clusters sur l'unite %d\n", ur.x.dx);

    */
    
    mes[0]=(char*)ur.x.ax;
    mes[1]=(char*)ur.x.bx;
    mes[2]=(char*)ur.x.cx;
    mes[3]=(char*)ur.x.dx;

    return *mes;
} 

char * disquecourant(){

    char *mes="";

    ur.h.ah = 0x19;

    int86(021, &ur, &urOut);


    /*

    printf("le numero du disque courant est %d", ur.h.al );

    */ 

    mes=(char*)ur.h.al;

    return mes;

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