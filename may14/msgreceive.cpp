//program for send message
#include<iostream>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 256
using namespace std;
struct mesg_buffer {
        long mesg_type;
        char mesg_text[MAX];
}mesg;

int main() {
        key_t key;
        int msgid;

        key = ftok("keyfile",65);
        msgid = msgget(key,0666 | IPC_CREAT);
        msgrcv(msgid,&mesg,sizeof(mesg),1,0);

        cout << "Data got from the  queue : " << mesg.mesg_text << endl;
        msgctl(msgid,IPC_RMID,NULL);
        return 0;
}
