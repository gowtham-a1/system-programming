#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<iostream>
void createShm(){
        key_t key = ftok("keyfile",65);
        int shm_id = shmget(key,1,0666 );
        if(shm_id == -1){
                perror("error creating shared memory");
                exit(EXIT_FAILURE);
	}
        short* no_of_connections = (short*)shmat(shm_id,(void*)0,0);
        *no_of_connections = 0;
}
void destroyShm(){
        key_t key = ftok("keyfile",65);
        int id = shmget(key,1,0666);
        shmctl(id,IPC_RMID,0);
}
short writetoShm(){
        key_t key = ftok("keyfile",65);
        int shm_id = shmget(key,1,0666 );
        if(shm_id == -1){
                perror("Error Accessing Shared Memory");
                exit(EXIT_FAILURE);
	}
        short* no_of_connections = (short*)shmat(shm_id,(void*)0,0);
.        *no_of_connections += 1;
        return *no_of_connections;
}
int createSocket(const char* ip,int port){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        std::cout << "socket error" << std::endl;
        return -1;
    }
    std::cout << "socket creation successfully" << std::endl;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int ret = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret < 0){
        std::cout << "bind error" << std::endl;
        return -1;
    }
    std::cout << "bind successfully" << std::endl;

    ret = listen(sock, 5);
    if(ret < 0){
        std::cout << "listen error" << std::endl;
        return -1;
    }
    std::cout << "listening on port "<< port << std::endl;
    return sock;
}
