/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Purpose :- Get relevent to POSIX,fork system calls

*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>
#include <sys/shm.h>

/*Child process creates*/
void generateCollatz(int n,void* sharedMemory){

			

		while(1){

			if(n == 1)
				break;
			else if(n&1)
				n = 3*n + 1;
			else
				n = n/2;

			sprintf(sharedMemory,"%d",n);
			int len = ceil(log10(n));
			if(len == log10(n))
				len++;
			sharedMemory += len;

			sprintf(sharedMemory,"%s"," ");
			sharedMemory += 1;
		}

		return;

}

int main(){

	printf("Enter number for Collatz Algorithm : ");
	int n;
	scanf("%d",&n);


	if(n > 0){


		const int SIZE = 8192;
		/*Name of Shared Memory*/
		const char *nameOfMemory = "Sid";
		/*Shared Memory file_descriptor*/
		int shm_fd;

		/*Pointer to shared memory*/
		void *sharedMemory;

		/* create the shared memory object */
		shm_fd = shm_open(nameOfMemory, O_CREAT | O_RDWR, 0777);

		ftruncate(shm_fd,SIZE);

		/* memory map the shared memory object */
		sharedMemory = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

		if(fork() == 0) 
			generateCollatz(n,sharedMemory);
		else{

			int status;
			wait(&status);

			printf("%s",(char *)sharedMemory);
			shm_unlink(nameOfMemory);

		}


	}
	else
		printf("Invalid");
	return 0;
	

}
