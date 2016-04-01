#include <stdlib.h>
#include <gtk/gtk.h>
#include "filefunc.h"


void on_activate_entry(GtkWidget *pEntry, gpointer data);
void on_copier_button(GtkWidget *pButton, gpointer data);
int auth(const gchar *username,const gchar *password);
void creationFenetre();
void getID(GtkWidget *pButton, gpointer data);
void login();
void ligneDeCommand(gchar* rep);


int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    login();
    gtk_main();

    return EXIT_SUCCESS;
}

/* Fonction callback execute lors du signal "activate"
    Y incorporer les socket afin de communiquer avec le Serveurs*/
void on_activate_entry(GtkWidget *pEntry, gpointer data)
{
    const gchar *sText;
    GtkTextBuffer *buf ;
    /* Recuperation du texte contenu dans le GtkEntry */
    sText = gtk_entry_get_text(GTK_ENTRY(pEntry));
    /* Modification du texte contenu dans le GtkLabel */
    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW ((GtkWidget*)data));
    gtk_text_buffer_set_text(buf, sText,-1);
}


int auth(const gchar* username,const gchar* password){
    /* Mansour tu pourra utiliser les variables username et password pour l'authentification */
    /* Utilise les sockets pour se connecter au Serveur.
       Verifie si le le Username et le mot de passe existe sur le Serveur
        Renvoie 1 si OK et 0 sinon */

    return 1;

}



void getID(GtkWidget *pButton, gpointer data){

    GtkWidget *pUsername;
    GtkWidget *pPassword;
    GtkWidget *pTempLabel;
    GList *pList;
    const gchar *username;
    const gchar *password;
    const gchar *msgErr;
    gchar* reps;

     /* Recuperation de la liste des elements que contient la GtkVBox */
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));

    pList = g_list_next(pList);
   // pList = g_list_next(pList);
     /* Le premier element est le GtkEntry Username */
    pUsername = GTK_WIDGET(pList->data);

     /* Passage a l element suivant : le GtkEntry  Password*/
    pList = g_list_next(pList);
    pList = g_list_next(pList);

     /* Récupération du deuxieme element  */
    pPassword = GTK_WIDGET(pList->data);

     /* on saute le bouton et le separator */
    pList = g_list_next(pList);
    pList = g_list_next(pList);
    pList = g_list_next(pList); // on récupère le label

     /* Récupération du label pour afficher des erreus au cas où*/
    pTempLabel=GTK_WIDGET(pList->data);

    /* recupération de la chaine de caractère contenu dans les Entrys */
    username=gtk_entry_get_text(GTK_ENTRY(pUsername));
    password=gtk_entry_get_text(GTK_ENTRY(pPassword));

    // Initialisation du Msg d'erreur
    msgErr="Login ou Pasword non autorisé ou inexistant";

    /* Liberation de la memoire utilisee par la liste */
    g_list_free(pList);

        if(strcmp(authentifierUser(username,password),"")!=0){
                // Connexion et authentification établie avec le Serveur ProgSys
                //   gtk_widget_destroy((GtkWidget*)data);
                    reps=authentifierUser(username,password);
                    strcat(reps,">");
                    ligneDeCommand((gchar*)reps);

        }
        else{
                /* Message d'Erreur */
                    gtk_label_set_text(GTK_LABEL(pTempLabel),msgErr);


        }
}

void login(){
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *username;
    GtkWidget *password;
    GtkWidget *pButton;
    GtkWidget *pLabel;
    GtkWidget *pLabelU;
    GtkWidget *pLabelP;
    GtkWidget *separator;

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Connexion ...");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 150, 150);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    pLabelU= gtk_label_new("Username :");
    gtk_box_pack_start(GTK_BOX(pVBox),pLabelU,TRUE,FALSE,0);
    gtk_label_set_justify (GTK_LABEL(pLabelU), GTK_JUSTIFY_LEFT );

    username=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox),username,TRUE,FALSE,0);

    pLabelP= gtk_label_new("Password :");
    gtk_box_pack_start(GTK_BOX(pVBox),pLabelP,TRUE,FALSE,0);
    gtk_label_set_justify (GTK_LABEL(pLabelP), GTK_JUSTIFY_LEFT );

    password=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox),password,TRUE,FALSE,0);

    separator = gtk_hseparator_new ();
    gtk_box_pack_start(GTK_BOX(pVBox),separator,TRUE,FALSE,0);

    pButton=gtk_button_new_with_label("Se Connecter");
    gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(getID), (GtkWidget*) pVBox);

    pLabel = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);

    gtk_widget_show_all(pWindow);
}


void ligneDeCommand(gchar* rep){
    GtkWidget *window;


    //rep=str_split("toto:momo:/home/momo",':');
    //reps=*(rep+2);
    // ------------------------- Creation de la ligne de commande ---------------------
    GtkWidget* textArea = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW (textArea), FALSE);
    GtkWidget* scrolledwindow = gtk_scrolled_window_new(NULL,NULL);
    GtkWidget* textEntry = gtk_entry_new();
    GtkWidget* console = gtk_table_new(3, 1, FALSE);
    GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textArea));
    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
    gtk_table_attach_defaults(GTK_TABLE(console), textArea, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(console), scrolledwindow, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(console), textEntry, 0, 2, 1, 2);
    gtk_widget_set_size_request(textArea, 320, 240);

    gtk_text_buffer_set_text(buf,rep, -1);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ligne de Commande");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_add(GTK_CONTAINER(window),console);

    // --------------------------------------------------------------------------------
    g_signal_connect(G_OBJECT(textEntry), "activate", G_CALLBACK(on_activate_entry), (GtkWidget*) textArea);
    //gtk_text_view_reset_cursor_blink(GTK_TEXT_VIEW (textArea));



    gtk_widget_show_all(window);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);


}
