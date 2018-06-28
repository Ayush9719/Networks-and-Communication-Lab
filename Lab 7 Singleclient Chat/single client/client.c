
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <string.h>
#include <unistd.h>
#define PORT 1248

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr; 
    char buff[20];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    memset(&serv_addr,'0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
     
   while(1)
{
    printf("Enter the string to echo: ");
    fgets(buff,sizeof(buff),stdin);
    write(sockfd,buff,sizeof(buff));
    strcpy(buff,"");
    printf("Msg received is: ");
    read(sockfd,buff,sizeof(buff));
    fputs(buff,stdout);
}
   
    close(sockfd);
         
    return 0;
}

