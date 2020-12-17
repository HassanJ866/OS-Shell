#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
void exec1();
void exec2();
void exec3();
void exec4();
void exec5();
void exec6();
void exec7();
void exec8();

int pid;
int pipe1[2];
int pipe2[2];
int pipe3[2];
char str[20];

void main() {
	//intro
		printf("\n*************************\n");
		printf("Welcome to our U Can't C Me CLI\n");
		printf("*************************\n");
		printf("List of commands you may use:\n");
		printf("1- calendar\n");
		printf("2- list\n");
		printf("3- longlist\n");
		printf("4- user\n");
		printf("5- day\n");
		printf("6- catwc\n");
		printf("7- numdir\n");
		printf("8- catsort\n");
		printf("9- printfile\n");
		printf("10- time\n");
		printf("*************************\n");
		printf("CopyWrite: Loay Khodor - Karem Al Aridi - Hassan Jaber\n");
		printf("OS Fall 2020\n");

fgets(str,20,stdin);
strtok(str,"\n");
//Exit
if(strcmp(str,"exit")==0){
	return;
}

//Help
if(strcmp(str,"help")==0){
		printf("*************************\n");
		printf("Welcome to our U Can't C Me CLI\n");
		printf("*************************\n");
		printf("List of commands you may use:\n");
		printf("1- calendar\n");
		printf("2- list\n");
		printf("3- longlist\n");
		printf("4- user\n");
		printf("5- day\n");
		printf("6- catwc\n");
		printf("7- numdir\n");
		printf("8- catsort\n");
		printf("9- printfile\n");
		printf("10- time\n");
		printf("*************************\n");
		printf("CopyWrite: Loay Khodor - Karem Al Aridi - Hassan Jaber\n");
		printf("OS Fall 2020\n");
}
//Calendar
if(strcmp(str,"calendar")==0)
execlp("cal","cal",NULL);
//List
if(strcmp(str,"list")==0)
execlp("ls","ls",NULL);
//Long List
if(strcmp(str,"longlist")==0)
execlp("ls","ls","-l",NULL);
//user
if(strcmp(str,"user")==0)
execlp("whoami","whoami",(char *)0);
//day
if(strcmp(str,"day")==0)
execl("/bin/date", "date", NULL);
//time
if(strcmp(str,"time")==0)
execlp("uptime", "uptime", NULL);

//CatWC DoublePipe
if(strcmp(str,"catwc")==0){
  if (pipe(pipe1) == -1) {
    perror("pipe1 failed");
    exit(1);
  }
  if ((pid = fork()) == -1) {
    perror("fork1 failed");
    exit(1);
  } else if (pid == 0) {
    exec1();
  }
  if (pipe(pipe2) == -1) {
    perror("pipe2 failed");
    exit(1);
  }
  if ((pid = fork()) == -1) {
    perror("fork2 failed");
    exit(1);
  } else if (pid == 0) {
    exec2();
  }
  close(pipe1[0]);
  close(pipe1[1]);

  if ((pid = fork()) == -1) {
    perror("fork3 failed");
    exit(1);
  } else if (pid == 0) {
    exec3();
  }
}

//NUmDir SinglePipe
if(strcmp(str,"numdir")==0){
  if (pipe(pipe1) == -1) {
    perror("pipe1 failed");
    exit(1);
  }
  if ((pid = fork()) == -1) {
    perror("fork1 failed");
    exit(1);
  } else if (pid == 0) {
    exec4();
  }
    exec5();
  close(pipe1[0]);
  close(pipe1[1]);
}
//CatSort SinglePiped
if(strcmp(str,"catsort")==0){
  if (pipe(pipe1) == -1) {
    perror("pipe1 failed");
    exit(1);
  }
  if ((pid = fork()) == -1) {
    perror("fork1 failed");
    exit(1);
  } else if (pid == 0) {
    exec6();
  }
    exec7();
  close(pipe1[0]);
  close(pipe1[1]);
}
// printfile SinglePipe
if(strcmp(str,"printfile")==0){
  pid_t pid ;
  int pipe3[2];
  pipe(pipe3);
  pid = fork(); 

  if(pid == 0) {
    exec6();
  }
  else if(pid > 0) {
    exec8();
  }
  else {
    printf("Error in forking");
    exit(1);
  }
  close(pipe3[0]);
  close(pipe3[1]);
}
}

void exec1() {
  // output to pipe1
  dup2(pipe1[1], 1);
  // close fds
  close(pipe1[0]);
  close(pipe1[1]);

  execlp("cat", "cat", "cmd.txt", NULL);
  perror("exec cat failed");
  _exit(1);
}

void exec2() {
  // input from pipe1
  dup2(pipe1[0], 0);
  // output to pipe2
  dup2(pipe2[1], 1);
  //close fds
  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);
  execlp("head", "head", "cmd.txt", "-n", "2", NULL);
  // read 2 lines from file cmd.txt
  perror("exec head failed");
  _exit(1);
}

void exec3() {
  // input from pipe2
  dup2(pipe2[0], 0);
  // output to stdout (already done)
  // close fds
  close(pipe2[0]);
  close(pipe2[1]);
  execlp("wc", "wc", "-w", NULL);
  // count the nbr of words
  perror("exec wc -w failed");
  _exit(1);
}

void exec4(){
  close(1);
  dup2(pipe1[1],1);
  close(pipe1[0]);
  close(pipe1[1]);

  execlp("ls", "ls", ".", NULL);
  //list the dir
  perror("execlp ls . failed");
  _exit(1);
}

void exec5(){
  dup2(pipe1[0],0);
  close(pipe1[1]);
  close(pipe1[0]);

  execlp("wc", "wc", "-l", NULL);
  //count dir
  perror("execlp wc -l failed");
  _exit(1);
}
void exec6(){
  close(1);
  dup2(pipe1[1],1);
  close(pipe1[0]);
  close(pipe1[1]);

  execlp("cat", "cat", "cmd.txt", NULL);
  //view cmd file
  perror("execlp cat failed");
  _exit(1);
}

void exec7(){
  dup2(pipe1[0],0);
  close(pipe1[1]);
  close(pipe1[0]);

  execlp("sort", "sort", NULL);
  //sort 
  perror("execlp sort failed");
  _exit(1);
}

void exec8(){
   dup2(pipe3[0],0);
   close(pipe3[0]);
   close(pipe3[1]);
   execlp("/bin/grep", "grep", "-c", "Apple" ,NULL);
   perror("execlp grep failed");
   exit(1);
}

