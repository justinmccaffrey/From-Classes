//Justin McCaffrey.31
//gcc OneCAnyP.c -o oc -lpthread -lrt

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *Cons (void *);
void *ProdA (void *);
void *ProdB (void *);

struct structA{
	int num;
	char chars[5];
};
struct structB{
	int num;
	char chars[3];
};
struct structA BufferA[20];
struct structB BufferB[40];

sem_t BufferAEmpty;
sem_t BufferBEmpty;
sem_t BuffersFull;
sem_t Mutex;
sem_t SyncA;
sem_t SyncB;

int a=0;

pthread_t tid[3];


int main(){
int i;
i=sem_init(&SyncA,0,0);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&SyncB,0,0);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&BufferAEmpty,0,20);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&BufferBEmpty,0,40);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&BuffersFull,0,0);
if(i<0){printf("sem init failed");exit(0);}
i=sem_init(&Mutex,0,1);
if(i<0){printf("sem init failed");exit(0);}
i=pthread_create(&tid[0],NULL,ProdA,NULL);
if(i<0){printf("thread create failed");exit(0);}
i=pthread_create(&tid[1],NULL,ProdB,NULL);
if(i<0){printf("thread create failed");exit(0);}
i=pthread_create(&tid[2],NULL,Cons,NULL);
if(i<0){printf("thread create failed");exit(0);}
for(i=0;i<3;i++){pthread_join(tid[i],NULL)==0;}
pthread_exit(NULL);
}


void * ProdA(void *arg){
	int i,in=0,x;
	struct structA itemA;
	x=sem_post(&SyncB);
	if(x<0){printf("sem operation failed");exit(0);}
	x=sem_wait(&SyncA);
	if(x<0){printf("sem operation failed");exit(0);}
	for(i=0;i<3000;i++){
		if((i+1)%2==0){strcpy(itemA.chars,"ABCaa");}
		else{strcpy(itemA.chars,"XYZxx");}
		itemA.num=i+1;
		x=sem_wait(&BufferAEmpty);
		if(x<0){printf("sem operation failed");exit(0);}
		BufferA[in]=itemA;
		x=sem_wait(&Mutex);
		if(x<0){printf("sem operation failed");exit(0);}		
		a=a+1;
		x=sem_post(&Mutex);
		if(x<0){printf("sem operation failed");exit(0);}
		x=sem_post(&BuffersFull);
		if(x<0){printf("sem operation failed");exit(0);}
		in=(in+1)%20;
		if((i+1)%500==0){usleep(100000);}
	}
pthread_exit(NULL);
}

void * ProdB(void *arg){
	int i,in,x;
	struct structB itemB;
	strcpy(itemB.chars,"MMM");
	x=sem_post(&SyncA);
	if(x<0){printf("sem operation failed");exit(0);}
	x=sem_wait(&SyncB);
	if(x<0){printf("sem operation failed");exit(0);}
	for(i=0;i<4000;i++){
		if(i==2000){strcpy(itemB.chars,"NNN");}
		itemB.num=i+1;
		x=sem_wait(&BufferBEmpty);
		if(x<0){printf("sem operation failed");exit(0);}		
		BufferB[in]=itemB;
		x=sem_post(&BuffersFull);
		if(x<0){printf("sem operation failed");exit(0);}
		in=(in+1)%40;
		if((i+1)%1000==0){usleep(200000);}
	}
pthread_exit(NULL);
}

void * Cons(void * arg){
	int i,outA=0, outB=0,x; 
	struct structA itemA; 
	struct structB itemB;
	char output[9];
	for(i=0;i<7000;i++){
		x=sem_wait(&BuffersFull); 
		if(x<0){printf("sem operation failed");exit(0);}
    		if (a>0){
			itemA=BufferA[outA];  
			outA=(outA+1) % 20;  
			x=sem_wait(&Mutex);
			if(x<0){printf("sem operation failed");exit(0);} 
			a= a-1;  
			x=sem_post(&Mutex);
			if(x<0){printf("sem operation failed");exit(0);}
			x=sem_post(&BufferAEmpty); 
			if(x<0){printf("sem operation failed");exit(0);}
			printf("%d%s ",itemA.num,itemA.chars);
        	} 
		else{
			itemB=BufferB[outB]; 
			outB=(outB+1) % 40;  
			x=sem_post(&BufferBEmpty); 
			if(x<0){printf("sem operation failed");exit(0);}
			printf("%d%s ",itemB.num,itemB.chars);
		} 
	
   	if((i+1)%2000==0){usleep(300000);}
   } 
pthread_exit(NULL);
}

