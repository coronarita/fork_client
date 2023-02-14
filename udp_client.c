#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

void error (char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
    int sock, length, n;
    struct sockaddr_in server, from;
    struct hostent *hp; // for changing format to host address from comand line

    char buffer[256];

    if (argc != 3) error("Usage: udp_client server_ip port");
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock <0 ) error("Socket Error");

    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if (hp==0) error("Error");

    // bcopy : copy the first source parameter to second position parameter about length
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, 
    hp->h_length);
    server.sin_port = htons(atoi(argv[2]));

    bcopy((char *)hp->h_addr, (char *)&server.sin_addr,
    hp->h_length);
    server.sin_port = htons(atoi(argv[2]));

    length = sizeof(struct sockaddr_in);

    // Send message
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    n = sendto(sock, buffer, strlen(buffer), 0, 
    (struct sockaddr *)&server, length);
    
    if (n<0) error("Send Error");

    write(1, "Got an message", 14);
    write(1, buffer, n);
    

}