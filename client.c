#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_UDP_PORT 1919
#define SERV_TCP_PORT 1919
#define SERV_HOST_ADDR "192.168.45.95"

char *pname;

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in serv_addr;
    pname = argv[0];

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        puts("Client: Error!");
        exit(1);

    }

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        puts("Client: connect error");
        exit(1);
    }

    if (write(sockfd, "HelloWorld\n", 20) < 20){
        puts("Client: write error");
        exit(1);
    }
    close(sockfd); 

    return 0;

}