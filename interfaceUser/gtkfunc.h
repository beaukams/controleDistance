#include "socketfunc.h"

void rechercherUserBis(GtkWidget *pButton, gpointer data){
     GList *pList;
     FILE * fichier = fopen("fichierUser.txt", "r");
     Personne p;
     char all[30000]="";
     char* nom="Username :";
     char* pass="\nPassword :";
     char* rep="\nRepdeBase :";
     gchar* msgError="Username inexsistant";

     GtkWidget *pUsername;
     GtkWidget *pPanel;
     const gchar *username;
     pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
     pList= g_list_next(pList);
     pUsername=GTK_WIDGET(pList->data);
     pList= g_list_next(pList);
     pList= g_list_next(pList);
     pList= g_list_next(pList);
     pPanel=GTK_WIDGET(pList->data);

     username=gtk_entry_get_text(GTK_ENTRY(pUsername));
if(fichier!=NULL){
     if(rechercheUser(username)==0){
            p=rechercheUser2(username);
            strcat(all,nom);
            strcat(all,p.login);
            //strcat(all,"\n");
            strcat(all,pass);
            strcat(all,p.mdp);
            //strcat(all,"\n");
            strcat(all,rep);
            strcat(all,p.rep);

            printf(all);
            gtk_label_set_text(GTK_LABEL(pPanel),(gchar*)all);
     }
     else{
            printf(msgError);
            gtk_label_set_text(GTK_LABEL(pPanel),msgError);

     }
}
else{
    printf("Fichier Error");
}
}

void supprimerUserBis(GtkWidget *pButton, gpointer data){
     GList *pList;
     GtkWidget *pUsername;
     const gchar *username;
     pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
     pList= g_list_next(pList);
     pUsername=GTK_WIDGET(pList->data);
     username=gtk_entry_get_text(GTK_ENTRY(pUsername));
     supprimerUser(username);

}

void ajouterUserBis(GtkWidget *pButton, gpointer data){

     GList *pList;
     GtkWidget *pUsername;
     GtkWidget *pPassword;
     GtkWidget *pRepertoire;
     const gchar *username;
     const gchar *password;
     const gchar *repertoire;
     char* outAjout;


     pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
     pList= g_list_next(pList);
     pUsername=GTK_WIDGET(pList->data);

     pList= g_list_next(pList);
     pList= g_list_next(pList);
     pPassword=GTK_WIDGET(pList->data);

     pList= g_list_next(pList);
     pList= g_list_next(pList);
     pRepertoire=GTK_WIDGET(pList->data);

     username=gtk_entry_get_text(GTK_ENTRY(pUsername));
     password=gtk_entry_get_text(GTK_ENTRY(pPassword));
     repertoire=gtk_entry_get_text(GTK_ENTRY(pRepertoire));

     outAjout=ajouterUser(username,password,repertoire);
     printf(outAjout);

}
void fenRechercheUser(GtkWidget *deleteTb, gpointer data){
    GtkWidget *pUser;
     GtkWidget *pLabelU;
     GtkWidget *pButton;
     GtkWidget *pLabel;
     GtkWidget *pSeparator;
     GtkWidget *pWindow;
     GtkWidget *pVBox;

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Rechercher User");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 150, 150);

    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    pLabelU= gtk_label_new("Username :");
    gtk_box_pack_start(GTK_BOX(pVBox),pLabelU,TRUE,FALSE,0);
    gtk_label_set_justify (GTK_LABEL(pLabelU), GTK_JUSTIFY_LEFT );

    pUser=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox),pUser,TRUE,FALSE,0);

    pSeparator = gtk_hseparator_new ();
    gtk_box_pack_start(GTK_BOX(pVBox),pSeparator,TRUE,FALSE,0);

    pButton=gtk_button_new_with_label("Rechercher User");
    gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(rechercherUserBis), (GtkWidget*) pVBox);

    pLabel = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);

    gtk_widget_show_all(pWindow);

}
void fenListerUser(GtkWidget *deleteTb, gpointer data){
    gchar* allUser;
    FILE* fichier;
    char chaine[500] = "";
    GtkWidget *window;
    GtkWidget* textArea = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW (textArea), FALSE);
    GtkWidget* scrolledwindow = gtk_scrolled_window_new(NULL,NULL);
    GtkWidget* ecran = gtk_table_new(1, 1, FALSE);
    GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textArea));
    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
    gtk_table_attach_defaults(GTK_TABLE(ecran), textArea, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(ecran), scrolledwindow, 0, 1, 0, 1);
    gtk_widget_set_size_request(textArea, 320, 320);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Liste des Utilisateurs du Systeme");
    gtk_container_add(GTK_CONTAINER(window),ecran);
    gtk_widget_show_all(window);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);//because of this
    allUser=(gchar*)listerUser2();

    gtk_text_buffer_set_text(buf,allUser ,-1);


}

void fenSupprimerUser(GtkWidget *deleteTb, gpointer data){
     GtkWidget *pUser;
     GtkWidget *pLabelU;
     GtkWidget *pButton;
     GtkWidget *pSeparator;
     GtkWidget *pWindow;
     GtkWidget *pVBox;

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Supprimer User");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 150, 150);

    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    pLabelU= gtk_label_new("Username :");
    gtk_box_pack_start(GTK_BOX(pVBox),pLabelU,TRUE,FALSE,0);
    gtk_label_set_justify (GTK_LABEL(pLabelU), GTK_JUSTIFY_LEFT );

    pUser=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox),pUser,TRUE,FALSE,0);

    pSeparator = gtk_hseparator_new ();
    gtk_box_pack_start(GTK_BOX(pVBox),pSeparator,TRUE,FALSE,0);

    pButton=gtk_button_new_with_label("Supprimer User");
    gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(supprimerUserBis), (GtkWidget*) pVBox);

    gtk_widget_show_all(pWindow);
}

void fenAjoutUser(GtkWidget *newTb, gpointer data){
    GtkWidget *pUser;
    GtkWidget *pLabelU;
    GtkWidget *pPass;
    GtkWidget *pLabelP;
    GtkWidget *pRep;
    GtkWidget *pLabelR;
    GtkWidget *pButton;
    GtkWidget *pSeparator;
    GtkWidget *pWindow;
    GtkWidget *pVBox;


    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Ajout User");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 150, 150);
    //g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    pLabelU= gtk_label_new("Username :");
    gtk_box_pack_start(GTK_BOX(pVBox),pLabelU,TRUE,FALSE,0);
    gtk_label_set_justify (GTK_LABEL(pLabelU), GTK_JUSTIFY_LEFT );

    pUser=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox),pUser,TRUE,FALSE,0);

    pLabelP= gtk_label_new("Password :");
    gtk_box_pack_start(GTK_BOX(pVBox),pLabelP,TRUE,FALSE,0);
    gtk_label_set_justify (GTK_LABEL(pLabelP), GTK_JUSTIFY_LEFT );

    pPass=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox),pPass,TRUE,FALSE,0);

    pLabelR= gtk_label_new("Repertoire de Base:");
    gtk_box_pack_start(GTK_BOX(pVBox),pLabelR,TRUE,FALSE,0);
    gtk_label_set_justify (GTK_LABEL(pLabelR), GTK_JUSTIFY_LEFT );

    pRep=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox),pRep,TRUE,FALSE,0);

    pSeparator = gtk_hseparator_new ();
    gtk_box_pack_start(GTK_BOX(pVBox),pSeparator,TRUE,FALSE,0);

    pButton=gtk_button_new_with_label("Ajouter User");
    gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(ajouterUserBis), (GtkWidget*) pVBox);

    gtk_widget_show_all(pWindow);

}
void fenServ(GtkWidget *startServerTb, gpointer data){
    GtkWidget *window;
    GtkWidget *textArea;
    GtkTextBuffer *buf;
    GList *pList;
    GtkTextIter start;
    GtkTextIter ends;
    gchar* cu;


    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
    textArea=GTK_WIDGET(pList->data);
    buf= gtk_text_view_get_buffer(GTK_TEXT_VIEW (textArea));
    gtk_text_buffer_get_start_iter(buf, &start);
    gtk_text_buffer_get_end_iter(buf, &ends);



    WSADATA	WSAData;
  	WSAStartup(MAKEWORD(2,2),&WSAData);

	//creation et parametrage du socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET csock;
	SOCKADDR_IN ssin, ccsin;
	ssin.sin_addr.s_addr = inet_addr("127.0.0.1");
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(PORT);

	//code a executer
  	printf("Demarrage du serveur sur le port %d...\n", PORT);
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"Serveur LOG");
    gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
    gtk_widget_show_all(window);
    int err_bind = bind(sock, (SOCKADDR*) &ssin, sizeof(ssin));
	listen(sock, 5);
	socklen_t taille = sizeof(ssin);

	while(true){
		csock = accept(sock, (SOCKADDR*)&ccsin, &taille);

        cu=gtk_text_buffer_get_text(buf,&start,&ends,FALSE);
		printf("connexion du client %s:%d...\n", inet_ntoa(ccsin.sin_addr), htons(ccsin.sin_port));
		strcat(cu,"\nConnexion du Client ");
        strcat(cu,inet_ntoa(ccsin.sin_addr));
        strcat(cu,":");
        strcat(cu,(char*)htons(ccsin.sin_port));
		//creation d'un thread pour gerer le client
		//pthread_t client;
		//int err_thr = pthread_create(&client, NULL, un_client, (void*) &csock);
        gtk_text_buffer_set_text(buf,cu,-1);
		un_client(&csock);
		break;

	}
	printf("fermeture de la socket serveur\n");
	closesocket(sock);

	WSACleanup();




}


void fenPrincipal (){



  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *toolbar;
  GtkToolItem *newTb;
  GtkToolItem *deleteTb;
  GtkToolItem *findTb;
  GtkToolItem *fileTb;
  GtkToolItem *sep;
  GtkToolItem *exitTb;
  GtkToolItem *startServerTb;
  GtkWidget* scrolledwindow= gtk_scrolled_window_new(NULL,NULL);;
  GtkWidget* textArea;
  GtkWidget* log;
  GtkTextBuffer *buf;
 // char cu[30000]="";


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window),"Serveur LOG");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  textArea= gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW (textArea), TRUE);

  log=  gtk_table_new(2, 1, FALSE);
  gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
  gtk_table_attach_defaults(GTK_TABLE(log), textArea, 0, 1, 0, 1);
  gtk_table_attach_defaults(GTK_TABLE(log), scrolledwindow, 0, 1, 0, 1);
  gtk_widget_set_size_request(textArea, 500, 500);
  gtk_text_buffer_set_text(buf,"--------------------------------------- Les Logs Du Serveur ---------------------------------------\n", -1);


 // gtk_container_add(GTK_CONTAINER(vbox),log);

  toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  newTb = gtk_tool_button_new_from_stock(GTK_STOCK_ADD);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);

  deleteTb = gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), deleteTb, -1);

  findTb = gtk_tool_button_new_from_stock(GTK_STOCK_FIND);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), findTb, -1);

  fileTb = gtk_tool_button_new_from_stock(GTK_STOCK_FILE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), fileTb, -1);

 // startServerTb= gtk_tool_button_new_from_stock(GTK_STOCK_NETWORK);
  //gtk_toolbar_insert(GTK_TOOLBAR(toolbar), startServerTb, -1);

  sep = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

  exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);

  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), log ,TRUE,FALSE,0);

  g_signal_connect(G_OBJECT(newTb), "clicked", G_CALLBACK(fenAjoutUser),(GtkWidget*) vbox );

  g_signal_connect(G_OBJECT(deleteTb), "clicked", G_CALLBACK(fenSupprimerUser), (GtkWidget*) vbox);

  g_signal_connect(G_OBJECT(findTb), "clicked", G_CALLBACK(fenRechercheUser), (GtkWidget*) vbox);

  g_signal_connect(G_OBJECT(fileTb), "clicked", G_CALLBACK(fenListerUser), (GtkWidget*) vbox);

  //g_signal_connect(G_OBJECT(startServerTb), "clicked", G_CALLBACK(fenServ), (GtkWidget*) vbox);

  g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

 gtk_widget_show_all(window);

}
