char* saisie(){
	char c;
	char *res = "";
	while((c=getchar()) != '\n' && c != '\r' && c != EOF){
		res = concatene(res, c);
	}
	
	return res;
}