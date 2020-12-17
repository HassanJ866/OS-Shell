#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h> 
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#define PORT 5100 

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
	//Socket initialization
		int server_fd, new_socket, valread; 
        struct sockaddr_in address;
        int opt = 1; 
        int addrlen = sizeof(address); 
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
        { 
                perror("socket failed"); 
                exit(1); 
        } 
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons( PORT ); 
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,                                                                    &opt, sizeof(opt))) 
        { 
                perror("setsockopt"); 
                exit(1); 
        } 

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
        { 
                perror("bind failed"); 
                exit(1); 
        } 
while(1){
        if (listen(server_fd, 3) < 0) 
        { 
                perror("listen"); 
                exit(1); 
        } 
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                                        (socklen_t*)&addrlen))<0) 
        { 
                perror("accept"); 
                exit(1); 
        }

sleep(1);
int fd[2];
pipe(fd);
pid_t pid = fork();

if(pid == 0){
	//read from client
char str[244];
read(new_socket,str,sizeof(str));
dup2(fd[1],STDOUT_FILENO);
close(fd[0]);
close(fd[1]);

//Exit
if(strcmp(str,"exit")==0){
	return;
}
//Help
if(strcmp(str,"help")==0){
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
        //End of Phase 1 & pid
    exit(1); 
}
wait(NULL);
	char* str_send[1024];
	dup2(fd[0],STDIN_FILENO);
	read(fd[0],str_send,1024);
    send(new_socket,str_send,1024,0);
    exit(1);
        	close(new_socket);
		}
         close(server_fd);
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

