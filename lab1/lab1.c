/*
Justin McCaffrey
CSE 2561 - M 8:00
Lab 1

This program accepts an integer between 1 and 200 exclusive, and returns the primes between 2 and that number and the number of twin prime pairs.
*/

#include <stdio.h> //for printf and scanf
#include <math.h>  //for sqrt

int isPrime(int);
int twinPrimesCount(int[],int);

main(){
int input,i,primeCount=0;
//ask for and read in input
printf("%s","Enter a positive integer greater than 1: ");
scanf("%d",&input);
int primes[input];
//check if the input is acceptable
if(input<200 && input>1){
	printf("Primes from 2 to %d: \n",input);
//check for and print primes between 2 and input
	for (i=2;i<=input;i++){
		if (isPrime(i)){
			primes[primeCount]=i;
			primeCount++;
			printf("%d  ",i);
		}
	}
//get and print number of pairs
printf("\nAmongst these there are %d twin primes.",twinPrimesCount(primes,primeCount));
}
}

//returns the number of pairs of 2 integers exactly 2 apart from the integers in the array
int twinPrimesCount(int primes[],int primeCount){
int count=0,i;
for(i=0;i<primeCount;i++){
if ((primes[i]+2)==primes[i+1] || (primes[i]+2)==primes[i+2])
	count++;
}
return count;
}

//returns whether the input number is prime as 0 or 1
int isPrime(int number){
int j;
	if(number==2)
		return 1;
	for (j=2;j<=sqrt(number);j++){
		if (number!=j && number%j==0)
			return 0;
	}
	return 1;
}
