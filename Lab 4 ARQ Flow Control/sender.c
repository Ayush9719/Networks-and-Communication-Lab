#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <string.h>
#include <unistd.h>
#define PORT 1999

#define FRAMELEN 4

typedef enum {
    SEND ,
    WAIT ,
    OVER

} state;

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
     const struct timeval sock_timeout={.tv_sec=2, .tv_usec=0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&sock_timeout, sizeof(sock_timeout));
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    state curstate=SEND;
    printf("Timeout is 2 secs\n");
    printf("Enter the string to send\n");
    fgets(buff,sizeof(buff),stdin);
    int datalen=strlen(buff);
    int datasent=0;
    char akg;
    //ARQ GOES HERE
    while(1){
        switch (curstate) {
            case SEND:
                printf("Sending Frame %d\n",datasent/4+1);
                write(sockfd,&buff[datasent],4);
                curstate=WAIT;
            break;
            case WAIT:
                recv(sockfd,&akg,1,0);
                if(akg=='p') //Positive reply 
                {
                    akg=' ';
                    datasent+=4;
                    if(datasent>=datalen){
                            printf("Successful Transmission\n");
                        return 0;
                    }
                    else
                        curstate=SEND;
                }else {
                    printf("Timeout reached\n");
                    curstate=SEND;
                }
            break;
        };
    }
    
    close(sockfd);
         
    return 0;
}
