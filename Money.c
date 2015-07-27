//Justin McCaffrey.31
//gcc Money.c -o Money -lpthread -lrt

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

void *Thread1 (void *);
void *Thread2 (void *);
void *Thread3 (void *);
void *Thread4 (void *);

pthread_t tid[4];
sem_t sync1;
sem_t sync2;
sem_t sync3;
sem_t sync4;
sem_t mutex;

int Account[3];

int main(){
int i;
Account[0]=100000;
Account[1]=100000;
Account[2]=100000;
i=sem_init(&sync1,0,0);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&sync2,0,0);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&sync3,0,0);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&sync4,0,0);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&mutex,0,1);
if(i<0){printf("sem init failed");exit(0);}
i=pthread_create(&tid[0],NULL,Thread1,NULL);
if(i<0){printf("thread create failed");exit(0);}
i=pthread_create(&tid[1],NULL,Thread2,NULL);
if(i<0){printf("thread create failed");exit(0);}
i=pthread_create(&tid[2],NULL,Thread3,NULL);
if(i<0){printf("thread create failed");exit(0);}
pthread_join(tid[i],NULL)==0;
pthread_exit(NULL);
}


void * Thread1(void *arg){
int i, internal_reg, x;
int Accts[3];
i=pthread_create(&tid[3],NULL,Thread4,NULL);
if(i<0){printf("thread create failed");exit(0);}
x=sem_post(&sync2);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync3);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
/*synch. with Thread2, Thread3 & Thread4 (4 proc 4 way synch.)*/
x=sem_wait(&sync1);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync1);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync1);
if(x<0){printf("sem operation failed");exit(0);}
for (i=0;i<10000;i++){
	x=sem_wait(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}
	internal_reg = Account [0];
	internal_reg = internal_reg - 100;
	Account[0] = internal_reg;
	/* same thing, except we're adding $100 to account1 now... */
	internal_reg = Account [1];
	internal_reg = internal_reg + 100;
	Account[1] = internal_reg;
	/* here add a code that outputs contents of each account and
	their sum after 1,000th, 2,000th, 3,000th, .... and 10,000th iteration*/
	Accts[0]=Account[0];
	Accts[1]=Account[1];
	Accts[2]=Account[2];
	x=sem_post(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}
	if((i+1)%1000==0){printf("Thread1:Account0:%d Account1: %d Account2: %d Sum: %d\n",Accts[0],Accts[1],Accts[2],(Accts[0]+Accts[1]+Accts[2]));}
	if((i+1)%3000==0){usleep(200000);} //wait .2 sec
}
x=sem_post(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
x=pthread_join(tid[3],NULL)==0;
if(x<0){printf("join failed");exit(0);}
pthread_exit(NULL);
} 

void * Thread2(void *arg){
int i, internal_reg, x;
int Accts[3];
x=sem_post(&sync1);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync3);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
/*synch. with Thread2, Thread3 & Thread4 (4 proc 4 way synch.)*/
x=sem_wait(&sync2);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync2);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync2);
if(x<0){printf("sem operation failed");exit(0);}
for (i=0;i<10000;i++){
	x=sem_wait(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}
	internal_reg = Account [1];
	internal_reg = internal_reg - 100;
	Account[1] = internal_reg;
	/* same thing, except we're adding $100 to account2 now... */
	internal_reg = Account [2];
	internal_reg = internal_reg + 100;
	Account[2] = internal_reg;
	/* here add a code that outputs contents of each account and
	their sum after 1,000th, 2,000th, 3,000th, .... and 10,000th iteration*/
	Accts[0]=Account[0];
	Accts[1]=Account[1];
	Accts[2]=Account[2];
	x=sem_post(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}
	if((i+1)%1000==0){printf("Thread2:Account0:%d Account1: %d Account2: %d Sum: %d\n",Accts[0],Accts[1],Accts[2],(Accts[0]+Accts[1]+Accts[2]));}
	if((i+1)==2000||(i+1)==4000||(i+1)==6000||(i+1)==9000){usleep(200000);} //wait .2 sec
}
x=sem_post(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
pthread_exit(NULL);
}

void * Thread3(void *arg){
int i, internal_reg,x;
int Accts[3];
x=sem_post(&sync1);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync2);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
/*synch. with Thread2, Thread3 & Thread4 (4 proc 4 way synch.)*/
x=sem_wait(&sync3);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync3);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync3);
if(x<0){printf("sem operation failed");exit(0);}
for (i=0;i<10000;i++){
	x=sem_wait(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}
	internal_reg = Account [2];
	internal_reg = internal_reg - 100;
	Account[2] = internal_reg;
	/* same thing, except we're adding $100 to account0 now... */
	internal_reg = Account [0];
	internal_reg = internal_reg + 100;
	Account[0] = internal_reg;
	/* here add a code that outputs contents of each account and
	their sum after 1,000th, 2,000th, 3,000th, .... and 10,000th iteration*/
	Accts[0]=Account[0];
	Accts[1]=Account[1];
	Accts[2]=Account[2];
	x=sem_post(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}
	if((i+1)%1000==0){printf("Thread3:Account0:%d Account1: %d Account2: %d Sum: %d\n",Accts[0],Accts[1],Accts[2],(Accts[0]+Accts[1]+Accts[2]));}
	if((i+1)==2000||(i+1)==7500){usleep(300000);} //wait .3 sec
}
x=sem_post(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
pthread_exit(NULL);
}

void * Thread4(void *arg){
int i, internal_reg,notEqual=0,x;
x=sem_post(&sync1);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync2);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_post(&sync3);
if(x<0){printf("sem operation failed");exit(0);}
/*synch. with Thread2, Thread3 & Thread4 (4 proc 4 way synch.)*/
x=sem_wait(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_wait(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
for (i=0;i<50000;i++){
	x=sem_wait(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}
	if((Account[0]+Account[1]+Account[2])!=300000){notEqual++;}
	x=sem_post(&mutex);
	if(x<0){printf("sem operation failed");exit(0);}	
	if((i+1)%10000==0){usleep(50000);}
}
printf("Thread4:Checked %d times. Not equal %d times.\n",i,notEqual);
int checksem=-1;
for(i=0;i<3;i++){pthread_join(tid[i],NULL)==0;}
x=sem_destroy(&sync1);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_destroy(&sync2);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_destroy(&sync3);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_destroy(&sync4);
if(x<0){printf("sem operation failed");exit(0);}
x=sem_destroy(&mutex);
if(x<0){printf("sem operation failed");exit(0);}
exit(0);
}
