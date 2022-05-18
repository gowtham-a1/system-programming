// Program to send message to a message queue
#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 256
using namespace std;

struct mesg_buffer
{
	long mesg_type;
	char mesg_text[MAX];
}mesg;

int main()
{
	key_t key;
	int msgid, err;

	key = ftok("keyfile", 65);
	msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
	if(msgid == -1)
	{
		perror("Error in creating message queue");
		exit(EXIT_FAILURE);
	}

	write(1, "Enter message to store: ", 25);
	read(0, mesg.mesg_text, MAX);
	mesg.mesg_type = 1;

	err = msgsnd(msgid, &mesg, sizeof(mesg), 0);
	if(err == -1)
	{
    	perror("Error in sending message to message queue");
		exit(EXIT_FAILURE);
	}

	cout << "Data sent to Queue: " << mesg.mesg_text << endl;
	

	return 0;
}
