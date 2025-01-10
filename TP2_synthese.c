#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#define BUF_SIZE 516 // entete 4o + data (max 512o)

int main(int argc, char ** argv) {
    printf("TFTP Client \n");
    //if correct number of arguments is provided (host, port, file)
    if (argc != 4){
         printf("Wrong command \n");
         exit(EXIT_FAILURE);
     }
   
    struct addrinfo hints;
    struct addrinfo * result;
    // Clear the hints structure to avoid undefined behavior
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_family = AF_INET; //IPv4 addresses
    hints.ai_protocol = IPPROTO_UDP;

    int status = getaddrinfo(argv[1],argv[2],&hints,&result);

    char ip_string[128]={0};
    char port_string[128]={0};

    getnameinfo(result->ai_addr,result->ai_addrlen,
             ip_string,128,port_string,128,
             NI_NUMERICHOST|NI_NUMERICSERV);

    printf("%s is resolved at : %s:%s",argv[1],ip_string,port_string);
    // Create a socket using the resolved address family, type, and protocol
    int sd = socket(result->ai_family,result->ai_socktype,
         result->ai_protocol);

    // TFTP Read Request (RRQ) message
    char rrq[128]={0};
    rrq[1]=1;
    sprintf(rrq+2,"%s",argv[3]);
    sprintf(rrq+3+strlen(argv[3]),"octet");

    // Send the RRQ message to the TFTP server
    sendto(sd,rrq,strlen(argv[3])+9,NULL,
        result->ai_addr,result->ai_addrlen);

    char buffer[BUFFER_SIZE];
    struct sockaddr server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // Receive data from the server (response or data packet)
    ssize_t n_bytes = recvfrom(sd, buffer, BUF_SIZE , 0, (struct sockaddr *)&server_addr, &addr_len)
    if (n_bytes<0){
        perror("Error data");
        exit(EXIT_FAILURE);}
    // Free the memory allocated for address resolution
    freeaddrinfo(result);


    return 0;
}
