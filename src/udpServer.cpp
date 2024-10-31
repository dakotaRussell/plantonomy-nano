#include "udpServer.h"

udpServer::udpServer()
{
    //ctor

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    readUdp();
}

const char* udpServer::readUdp()
{
    std::cout<<"Read request."<<std::endl;
    socklen_t len;
    int n;
    len = sizeof(cliaddr);  //len is value/result
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("UdpServerRead : \"%s\"\n", buffer);
    return buffer;
}

void udpServer::writeUdp(const char* message)
{
    printf("UdpServerWrite : \"%s\"\n", message);
    socklen_t len = sizeof(cliaddr);
    sendto(sockfd, (const char *)message, strlen(message),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    std::cout<<"Message sent."<<std::endl;
}

udpServer::~udpServer()
{
    //dtor
}
