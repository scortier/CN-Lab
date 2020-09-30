#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{
    printf("****Type a Message to Send to Exit type quit****\n");
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char hello[100];
    // printf("Type a Message to send: \t");
    // fgets(hello,sizeof(hello)+1,stdin);
    //hello[99]='\0';
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    // send(sock , hello , strlen(hello) , 0 ); 
    // valread = read( sock , buffer, 1024); 
    // printf("Message Received is \t%s\n",buffer );
    while(1){
        printf("Type a Message to Send:\t");
        fgets(hello,sizeof(hello)+1,stdin);
        hello[99]='\0';

        if(strncmp("quit",hello,4)==0){
            printf("Chat Ended\n");
            send(sock , "quit" , 5 , 0 );
            exit(0);
        }

        send(sock , hello , sizeof(hello)+1 , 0 ); 
        valread = read( sock , buffer, 1024);

        if(strncmp("quit",buffer,4)==0){
            printf("Chat Ended\n");
            //send(sock , "quit" , 5 , 0 );
            exit(0);
        }
        
        printf("Message Received is:\t%s",buffer );
    }
       
        
    
    return 0; 
} 
