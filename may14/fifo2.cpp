// Program to implement fifo
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#define MAX 256
using namespace std;

int main()
{
        char fifoname[] = "fifotest";
        int fifofd, ret;
        char readbuff[MAX], writebuff[MAX];
        mkfifo(fifoname, 0666);
        while(1)
        {
                memset(readbuff, 0 , MAX);
                memset(writebuff, 0 , MAX);

                fifofd = open(fifoname, O_WRONLY);
                write(1, "Enter your message: ", 20);
                ret = read(0, writebuff, MAX);
                write(fifofd, writebuff, ret);
                close(fifofd);

                if(strcmp("BYE\n", writebuff) == 0)
                        break;

                fifofd = open(fifoname, O_RDONLY);
                ret = read(fifofd, readbuff, MAX);
                write(1, "Message from Friend: ", 21);
                write(1, readbuff, ret);
                write(1, "\n", 1);
                close(fifofd);

                if(strcmp("BYE\n", readbuff) == 0)
                        break;
        }

        return 0;
}
