#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define PORT 1248

int main(int argc, char *argv[])
{
    char buffer[20];
    int sockfd,a,connfd,len,pid;
    struct sockaddr_in servaddr,cliaddr;
    
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
    while(1)
    {
        len=sizeof(cliaddr);
        connfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
        pid=fork();
        if(pid==0)
    {   close(sockfd);
        while(1)
       {
        strcpy(buffer,"");
        read(connfd,buffer,sizeof(buffer));
        printf("Msg received is :%s",buffer);
        printf("Enter your msg : ");
        fgets(buffer,sizeof(buffer),stdin);
        write(connfd,buffer,sizeof(buffer));
       }
    }
       else
          close(connfd);  
    } 
      
}
