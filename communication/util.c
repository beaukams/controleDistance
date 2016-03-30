#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char * concatene(char* str, char c){
	int t=strlen(str);
	char * res = (char*) malloc(sizeof(char)*(t+1));
	int i=0; 
	for(i=0; i<t; i++)
		res[i] = str [i];
	res[t] = c;
	return res;
}

char * str_concatene(char* str, char* strc){
	int t=strlen(str);
	int tc=strlen(strc);
	char * res = (char*) malloc(sizeof(char)*(t+tc));
	int i=0; 
	for(i=0; i<t; i++)
		res[i] = str [i];
	for(i=0; i<tc; i++)
		res[i+t] = strc [i];
	
	return res;
}

char** str_split(char* str, char delim){
	
	int t = strlen(str);
	int nb_tokens = 1;
	int i=0;
	for(i=0; i<t; i++){
		if(str[i] == ' ')
			nb_tokens++;
	}

	char ** tab_res = (char**) malloc(sizeof(char*)*nb_tokens);
	int index = 0;
	for(i=0; i<nb_tokens; i++){
		tab_res[i] = "";
		
		char c;
		do{
			c = str[index];
			if(c != ' ' && c != '\0')
				tab_res[i] = concatene(tab_res[i],c);
			index++;
		}while(c != ' ' && c != '\0');
	}
	return tab_res;
}

