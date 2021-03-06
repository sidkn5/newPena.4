<<<<<<< HEAD
/*
Student: Sean Dela Pena
Professor: Dr. Sanjiv Bhatia
Date: 4/4/2021

*/


=======
>>>>>>> d2994e983fc1b930a6cdbc7f09177c00fb22e908
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <errno.h>
#include <time.h>

#include "functionheader.h"

int shmid;
int semid;
int userInd;
int userPid;
int seconds;
char logfile[30];

FILE* fp;
holder* shmPtr;

void handler(){
	shmdt(shmPtr);
}


int main(int argc, char* argv[]) {

	srand(time(NULL));
	int num;
	int times;
	int burstTime;
	float timeInMs;
	float timeInNano;
	int randomNum;
	key_t shmKey = ftok("./README.md", 'a');
	key_t semKey = ftok("./Makefile", 'a');
	signal(SIGKILL, handler);
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	
	randomNum = rand() % 10000;

	sprintf(logfile, "%d.log", randomNum);
	fp = fopen(logfile, "a");


	//attach to shared memory
	shmid = shmget(shmKey, (sizeof(processControlBlock)) + sizeof(holder), IPC_EXCL);
	if (shmid < 0) {
		perror("user: Error: shmget error, creation failure.\n");
		handler();
		exit(1);
	}

	shmPtr = (holder*)shmat(shmid, NULL, 0);
	if (shmPtr == (holder*)-1) {
		perror("user: Error: shmget error, creation failure.\n");
		handler();
		exit(1);
	}

	//make semaphores
	
	semid = semget(semKey, 1, IPC_EXCL);
	if (semid < -1) {
		perror("user: Error: semget error, creation failure.\n");
	}

	userPid = getpid();


	//Clean up
	handler();



	return 0;


	//////////END OF MAIN//////////////
}
