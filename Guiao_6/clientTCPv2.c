#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 20
#define PORT 5005
#define SA struct sockaddr

struct header {

    char version;
    long order;
    long size;
    char message[20];
};

void func(int sockfd)
{
    char buff[MAX];
    int order = 1;
    int textsize=0;
    for (;;) {

        //Fill out the message with '-' for padding
        memset(buff, 45, sizeof(buff));


        printf("Message to send? [max 20 chars]? ");
        fgets(buff,MAX,stdin);

        //Delete the trailing new line
        buff[strcspn(buff, "\n")] = 0;
        textsize= strlen(buff);

        if (strlen(buff)<20){
            for (int i = strlen(buff);i<20;i++)
                buff[i]='-';
        }

        struct header msg; 
        msg.version='1';
        msg.order= order++;
        msg.size=textsize;
        strcpy(msg.message, buff);

        write(sockfd, &msg, sizeof(struct header));

    }
}
   
int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cli;
   
    printf("Press Ctrl+C to exit...\n");

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
       
    // function for chat
    func(sockfd);
   
    // close the socket
    close(sockfd);
}