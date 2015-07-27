//Justin McCaffrey.31
//gcc MatrixMul.c -o mm -lpthread -lrt
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int n=1200,m=1000,p=500;
int a[1200][1000];
int b[1000][500];
int c1[1200][500];
int c[1200][500];
int threads;
int thread[6]={0,1,2,3,4,5};

pthread_t tid[5];
void *Thread0 (void * thread);

void createThreads(int numThreads){
	int i,c;
	struct timeval tv,tv2;
	threads=numThreads;
	gettimeofday(&tv,NULL);
	for(i=0;i<threads;i++){
		c=pthread_create(&tid[i],NULL,Thread0,&thread[i]);
	}
	if(c<0){printf("thread create failed");exit(0);}
	for(i=0;i<threads;i++){pthread_join(tid[i],NULL)==0;}
	gettimeofday(&tv2,NULL);
	printf("%d\t%.2f\n",threads,tv2.tv_sec+(tv2.tv_usec/1000000.0)-tv.tv_sec+(tv.tv_usec/1000000.0));
	if(checkC()){printf("Comparison: No error\n");}
}

void multiply(int threadNum,int totalThreads){
	int i,j,k,startIndex,endIndex;
	startIndex=threadNum*(n/totalThreads);
	endIndex=startIndex+(n/totalThreads);
	for(i=startIndex;i<endIndex;i++){
		for(j=0;j<p;j++){
			c[i][j]=0;
			for(k=0;k<m;k++){
				c[i][j]+=a[i][k]*b[k][j];
}}}}

int checkC(){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<p;j++){
			if(c[i][j]!=c1[i][j]){return 0;}
	}}
	return 1;
}

int main(){
int i,j,k;
double timeDif;
struct timeval tv,tv2;
for(i=0;i<n;i++){
	for(j=0;j<m;j++){
		a[i][j]=i*j;	
	}
}
for(i=0;i<m;i++){
	for(j=0;j<p;j++){
		b[i][j]=i+j;	
	}
}
printf("Threads\tSeconds\n");
//1thread
gettimeofday(&tv,NULL);
for(i=0;i<n;i++){
	for(j=0;j<p;j++){
		c1[i][j]=0;
		for(k=0;k<m;k++){
			c1[i][j]+=a[i][k]*b[k][j];
}}}
gettimeofday(&tv2,NULL);
printf("1\t%.2f\n\n",tv2.tv_sec+(tv2.tv_usec/1000000.0)-tv.tv_sec+(tv.tv_usec/1000000.0));
//2-6threads
for(i=2;i<=6;i++){createThreads(i);}
}//end main

void * Thread0(void *thread){
	int* threadNum=(int*)thread;
	multiply(*threadNum,threads);
	pthread_exit(NULL);
}



