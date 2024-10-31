#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

class udpServer
{
    public:
        udpServer();
        const char* readUdp();
        void writeUdp(const char* message);
        virtual ~udpServer();

    protected:

    private:
        int sockfd;
        char buffer[MAXLINE];
        struct sockaddr_in servaddr, cliaddr;

};

#endif // UDPSERVER_H
