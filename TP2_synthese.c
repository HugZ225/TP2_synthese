#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#define BUF_SIZE 516 // entete 4o + data (max 512o)

int main(int argc, char ** argv) {
    printf("TFTP Client \n");

    if (argc != 4){
         printf("Wrong command \n");
         exit(EXIT_FAILURE);
     }

    struct addrinfo hints;
    struct addrinfo * result;
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;

    int status = getaddrinfo(argv[1],argv[2],&hints,&result);

    char ip_string[128]={0};
    char port_string[128]={0};

    getnameinfo(result->ai_addr,result->ai_addrlen,
             ip_string,128,port_string,128,
             NI_NUMERICHOST|NI_NUMERICSERV);

    printf("%s is resolved at : %s:%s",argv[1],ip_string,port_string);

    int sd = socket(result->ai_family,result->ai_socktype,
         result->ai_protocol);

    char rrq[128]={0};
    rrq[1]=1;
    sprintf(rrq+2,"%s",argv[3]);
    sprintf(rrq+3+strlen(argv[3]),"octet");

    sendto(sd,rrq,strlen(argv[3])+9,NULL,
        result->ai_addr,result->ai_addrlen);

    char buffer[BUFFER_SIZE];
    struct sockaddr server_addr;
    socklen_t addr_len = sizeof(server_addr);

    ssize_t n_bytes = recvfrom(sd, buffer, BUF_SIZE , 0, (struct sockaddr *)&server_addr, &addr_len)
    if (n_bytes<0){
        perror("Error data");
        exit(EXIT_FAILURE);}


    freeaddrinfo(result);


    return 0;
}
