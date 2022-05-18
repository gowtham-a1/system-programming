// Program to demonstrate a race condition
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int balance = 0;
sem_t sem1;

void* computebalance(void* arg)
{
	int b, c;
	cout << "Balance calculation start" << endl;
	sem_wait(&sem1);
	b = balance;
	for(int i = 0; i < 50000; i++)
	{
		c = 5000 * 1234;
	}
	sleep(1);
	b += 10;
	balance = b;
	sem_post(&sem1);
	cout << "Balance calculation complete" << endl;

	return NULL;
}

int main()
{
	int  i;
	pthread_t thread_id[200];
	sem_init(&sem1, 0, 1);

	cout << "Balance before thread: " << balance << endl;

	for(i = 0; i < 200; i++)
	{
		pthread_create(&thread_id[i], NULL, computebalance, NULL);
	}

	for(i = 0; i < 200; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	sem_destroy(&sem1);
	cout << "Balance after thread: " << balance << endl;

	exit(EXIT_SUCCESS);
}
