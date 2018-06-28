#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 1999

#define FRAMELEN 4
int main(int argc, char *argv[])
{
    char buffer[6];
    buffer[5]='\0';
    int sockfd,a,connfd,len;
    struct sockaddr_in servaddr,cliaddr;
    const char akg='p';
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
       printf("Error creating socket\n");
       
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if((a=listen(sockfd,5))<0)
             printf("Error in LISTEN function");

    while(TRUE)
    {
        len=sizeof(cliaddr);
        printf("Server started\n");
        connfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
        printf("Accepted client request");
        while(1){
            strcpy(buffer,"");
            read(connfd,buffer,4);
            printf("\nMsg received :%s",buffer);
            int delayms=rand() % 4;
            printf("\nSimulating delay of %d s before sending AKG.",delayms);
            sleep(delayms);
            write(connfd,&akg,1);
            printf("\nSent AKG\n\n");
        }
    }
    close(sockfd); 
}
