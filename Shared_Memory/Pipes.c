// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <ctype.h>

char* getInverted(char str[]){

	int i;
	for(i = 0;i<strlen(str);i++){

		if(islower(str[i]))
			str[i] = toupper(str[i]);
		else if(isupper(str[i]))
			str[i] = tolower(str[i]);
		else
			continue;
	}

	return str;
}

int main(){

	int ParentWrite[2],ClientWrite[2];

	if (pipe(ParentWrite)==-1) { 
        	printf("Pipe Failed" ); 
        	return 1; 
    	} 
    	if (pipe(ClientWrite)==-1){ 
        	printf("Pipe Failed" ); 
        	return 1; 
    	} 


	if(fork() > 0){

		/*Parent Process*/
		printf("Parent Process Started\n");

		printf("Enter String to Inverted :- ");
		char input[100];
		scanf ("%[^\n]%*c", input);

		write(ParentWrite[1],input,strlen(input)+1);
		
		wait(NULL);

		char out[100];
		read(ClientWrite[0],out,101);

		printf("Inverted String is  : - %s \n",out);
	}else{

		 
  
        	char str[100];
		read(ParentWrite[0],str,101);

		int k = strlen(str);
		str[k] = '\0';

		char* ptr = getInverted(str);

		write(ClientWrite[1],ptr,101);
	}
}
