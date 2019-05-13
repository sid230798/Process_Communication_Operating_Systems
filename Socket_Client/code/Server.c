/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 18/11/18
Purpose :-

	1. Acts as Server
	2. Takes info from client 
	3. Sends back ans

*/

/*Libraries for IPC*/
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
#include "message.h"
#include <stdlib.h>

/*-------------------------------------------------------------------------------------------*/

float getConversion(char[]);

/*Contact Web and get the INR conversion*/
float getConversion(char str[]){

	/*Create Complete Url as this*/
	char dst[500] = "http://free.currencyconverterapi.com/api/v5/convert?q=INR_";
	strcat(dst,str);
 	strcat(dst,"&compact=y");

	char addr[500] = "wget -q '";
	strcat(addr,dst);
	strcat(addr,"' -O -> data.json");
	/*System Call for requesting JSON-File*/
	system(addr);

	/*open file data.json which stores data requested*/
	FILE* f = fopen("data.json","r");
	if(!f){

		printf("Unable to Open\n");
		return -1;

	}
	
	/*Get the complete Line to extract value*/
	char line[50];
	fgets(line, 50, f);
	
	/*Get the index first digit and first ending bracket and output*/
	int indexOfColon = strcspn(line, "0123456789") - 1;
	int endindex = strcspn(line, "}");

	/*Value stores the value in json file acquired by substring operation using memcpy*/	
	char Value[30] = {0};
	memcpy(Value, line + indexOfColon +1, endindex - indexOfColon);

	float ans = atof(Value);

	return ans;

}

/*-----------------------------------------------------------------------------------------*/

int main(){

	printf("You can press Ctrl-C anytime you want to exit.\n");

	/*Create Shared IPC memory for Process with secrete key as 97*/
	key_t secret_key = ftok("SharedMemory", 97);

	/*Creates 1024 bytes memory*/
	int shmid = shmget(secret_key, 1024, 0666|IPC_CREAT); 

	/* shmat to attach to shared memory */
	struct Message *val = (struct Message*) shmat(shmid, (void*)0, 0); 
	val->request = 1;

	/*Wait for Clients to Join*/	
	while(1){
	
		printf("Waiting for next request .......\n\n");
		while(strcmp(val->str, "") == 0);
		
		printf("Request received for : %s\n",val->str);
		printf("Contacting Web Service ........\n");
		val->parsedValue = getConversion(val->str);
		printf("INR_%s conversion is : %f\n\n\n",val->str,val->parsedValue);

		val->request = 2;
		//float val = getConversion(val->str);
		//printf("Recieved This : %f",val);
		if(strcmp(val->str, "exit") == 0){
			strcpy(val->str, "");
			val->request = 0;
			break;
		}

		strcpy(val->str, "");
	}
	

	shmdt(val);
	shmctl(shmid,IPC_RMID,NULL); 

	return 0;

}

/*---------------------------------------------------------------------------------------------------*/
