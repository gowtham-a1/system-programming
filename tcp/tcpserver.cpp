// Program to create a test TCP server
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
        struct sockaddr_in servaddr, cliaddr;
        char smsg[MAX], cmsg[MAX];
        int sockfd, connfd, mlen, slen, ret;
        socklen_t clen;
        pid_t client_pid;

        slen = sizeof(sockaddr_in);
        memset(&servaddr, 0, slen);
        memset(&cliaddr, 0, slen);
        memset(smsg, 0, MAX);
        memset(cmsg, 0, MAX);

        servaddr.sin_family = AF_INET; // using internet family of addressing - IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(PORTNO);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        handleError(sockfd, "Error: Unable to create socket");
        ret = bind(sockfd, (struct sockaddr *)&servaddr, slen);
        handleError(ret, "Error: Unable to bind socket");
        ret = listen(sockfd, 5);
        handleError(ret, "Error: Unable to listen on socket");

        while(1)
        {
                connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clen);
                handleError(connfd, "Error: Unable to accept connection");

                client_pid = fork();
                if(client_pid == 0)
                {
                        close(sockfd);
                        mlen = read(connfd, cmsg, MAX);
                        write(1, "Client: ", 8);
                        write(1, cmsg, strlen(cmsg));

                        write(1, "Enter message for client: ", 26);
                        mlen = read(0, smsg, MAX);
                        mlen = write(connfd, smsg, strlen(smsg));

                        write(1, "Message sent from server\n", 32);

                        close(connfd);
                        exit(EXIT_SUCCESS);
                }

                close(connfd);
        }

        return 0;
}
