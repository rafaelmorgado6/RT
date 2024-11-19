// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
#define PORT     5005
#define MAXLINE 1024
#define MAX_LIMIT 20
   
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    //char *hello = "Hello from client";
    char hello[MAX_LIMIT];
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    //Note: if you wanto to use other IP address, load it with inet_aton()
    //Example: inet_aton("63.161.169.137", &servaddr.sin_addr.s_addr);
       
    int n, len;
    
    while(1){
      
        printf("Message to send? \n");
        fgets(hello, MAX_LIMIT, stdin);

        sendto(sockfd, (const char *)hello, strlen(hello),
            MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                sizeof(servaddr));
        printf("Hello message sent.\n");

        /*    
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
        */
    }

    close(sockfd);
    return 0;
}