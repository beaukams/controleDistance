#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void str_split(char* str, char delim){
	//compte le nombre de tokens
	int t = strlen(str);
	int nb_tokens = 1;
	int i=0;
	for(i=0; i<t; i++){
		if(str[i] == ' ')
			nb_tokens++;
	}

	char ** tab_res = (char**) malloc(sizeof(char*)*nb_tokens);
	for(i=0; i<nb_tokens; i++){
		tab_res[i] = "";
		
	}
}

void main(){
	char * ch = "bonjour monsiueur kama";
	str_split(ch, ' ');
}