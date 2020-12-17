#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define PORT 5100 

int main(int argc, char const *argv[]) 
{ 
        int sock = 0; 
        struct sockaddr_in serv_addr; 
        char buffer[1024] = {0}; 
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        { 
                printf("Socket creation error \n"); 
                return -1; 
        } 

        serv_addr.sin_family = AF_INET; 
        serv_addr.sin_port = htons(PORT); 
        
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
        { 
                printf("Address not supported \n"); 
                return -1; 
        } 

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        { 
                printf("Connection Failed \n"); 
                return -1; 
        }

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
        printf("OS Fall 2020\n\n\n");
        printf("Enter Command:\n");
        
        //Send command to Server
        printf("\n");
        char* str;
        fgets(str,20,stdin);
        strtok(str,"\n");
        send(sock,str,strlen(str),0);
        printf("\n");
        char read_str[1024];
        read(sock,read_str,sizeof(read_str)); 
        printf("%s\n", read_str);
        sleep(1);

        close(sock);       
        return 0; 
} 

