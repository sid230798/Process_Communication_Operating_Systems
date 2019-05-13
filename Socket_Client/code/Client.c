/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 18/11/18
Purpose :-

	1. Acts as Server
	2. Takes info from client 
	3. Sends back ans

*//*Libraries for IPC*/
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include "message.h"

int main(){

	printf("You can press Ctrl-C anytime you want to exit.\n");

	/*Create Shared IPC memory for Process with secrete key as 97*/
	key_t secret_key = ftok("SharedMemory", 97);

	/*Creates 1024 bytes memory*/
	int shmid;

	/*Wait while Server is Created*/
	while((shmid = shmget(secret_key, 1024, 0666)) < 0) ; 

	/* shmat to attach to shared memory */
	struct Message *val = (struct Message*) shmat(shmid, (void*)0, 0); 
	val->request = 1;
	
	/*Keep on Reqesting for COnversions and Output for each of it*/
	while(1){	

		/*Take Input from User for Currency conversion*/
		printf("Currency Code (e.g. USD, GBP, etc.) : ");
		scanf("%s", val->str);

		printf("Waiting for Servers Response ......\n");

		while(val->request == 1) ;

		printf("Conversion rate wrt INR: %f\n\n\n",val->parsedValue);
		val->request = 1;

	}

	return 0;
}

/*-------------------------------------------------------------------------------------*/
