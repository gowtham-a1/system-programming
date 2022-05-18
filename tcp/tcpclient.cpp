// Program to create a test TCP client
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX 256
#define ADDRSERV "127.0.0.1"
#define PORTNO 8007
using namespace std;

int handleError(int status, const char errmsg[])
{
        if(status < 0)
        {
                perror(errmsg);
                exit(EXIT_FAILURE);
        }
        return 0;
}

int main(int argc, char* argv[])
{
        struct sockaddr_in servaddr;
        char smsg[MAX], cmsg[MAX];
        int sockfd, mlen, slen, ret;

        slen = sizeof(sockaddr_in);
        memset(&servaddr, 0, slen);
        memset(smsg, 0, MAX);
        memset(cmsg, 0, MAX);

        servaddr.sin_family = AF_INET; // using internet family of addressing - IPv4
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORTNO);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        handleError(sockfd, "Error: Unable to create socket");

        ret = connect(sockfd, (struct sockaddr *)&servaddr, slen);
        handleError(ret, "Error: Unable to make connection");

        write(1, "Enter message for server: ", 26);
        mlen = read(0, cmsg, MAX);
        mlen = write(sockfd, cmsg, strlen(cmsg));

        write(1, "Message sent from client\n", 32);

        mlen = read(sockfd, smsg, MAX);
        write(1, "Server: ", 8);
        write(1, smsg, strlen(smsg));

        close(sockfd);

        return 0;
}
