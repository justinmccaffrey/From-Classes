#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer{
	char id[16];
	char first[64];
	char last[64];
	double total;
};

int main(int argc, char *argv[])
{    
	int numberNames=0, numberPurchs=0;
	char ch;
	if(argc<5)
		printf("Please provide all command line arguments");
	else{
		FILE  *names,*purchs,*out;
		names=fopen(argv[1],"r");
		purchs=fopen(argv[2],"r");
		out=fopen(argv[3],"w");
		if(names==NULL ||purchs==NULL||out==NULL){
			perror("Error while opening the file.\n");
			exit(EXIT_FAILURE);
		}
		while(!feof(names)) //find how many names are in customer file
		{
	  		ch = fgetc(names);
	  		if(ch == '\n')
	  		{
				numberNames++;
	  		}
		}
		rewind(names);
		struct customer *customers;	
		customers=(struct customer *)calloc(sizeof(struct customer),numberNames);
		int i,j;
		char *temp=(char*)malloc(500*sizeof(char));
		char id[64];
		for (i=0;i<numberNames;i++){ //fill array with customer info
			fgets(temp,500,names);
			strcpy(customers[i].id,strtok(temp," \n"));
			strcpy(customers[i].first,strtok(NULL," \n"));
			strcpy(customers[i].last,strtok(NULL," \n"));
			customers[i].total=0;
		}
		while(!feof(purchs)) //find how many transactions to process
		{
	  		ch = fgetc(purchs);
	  		if(ch == '\n')
	  		{
				numberPurchs++;
	  		}
		}
		rewind(purchs);
		for(i=0;i<numberPurchs;i++){ //process transactions
			fgets(temp,500,purchs);
			strcpy(id,strtok(temp," \n"));
			for(j=0;j<numberNames;j++){
				if(strcmp(customers[j].id,id)==0){
					strcpy(temp,strtok(NULL," \n"));
					customers[j].total+=atof(temp);
				}
			}
		}
		struct customer *tempC;
		tempC=(struct customer*)malloc(sizeof(struct customer));	
		switch (atoi(argv[4])){//sort and print to output file based on last command line argument
		case 0://id
			for(i=0;i<numberNames;i++){
				for (j=i+1;j<numberNames;j++){
					if(strcmp(customers[i].id,customers[j].id)>0){
						*tempC=customers[i];
						customers[i]=customers[j];
						customers[j]=*tempC;
					}
				}
			}
			for(i=0;i<numberNames;i++){
				fputs(customers[i].first,out);
				fputs("\t",out);
				fputs(customers[i].last,out);
				fputs("\t",out);
				snprintf(temp,100,"%.2f",customers[i].total);
				fputs(temp,out);
				fputs("\n",out);
			}
			break;
		case 1://first name
			for(i=0;i<numberNames;i++){
				for (j=i+1;j<numberNames;j++){
					if(strcmp(customers[i].first,customers[j].first)>0){
						*tempC=customers[i];
						customers[i]=customers[j];
						customers[j]=*tempC;
					}
				}
			}
			for(i=0;i<numberNames;i++){
				fputs(customers[i].first,out);
				fputs("\t",out);
				fputs(customers[i].last,out);
				fputs("\t",out);
				snprintf(temp,100,"%.2f",customers[i].total);
				fputs(temp,out);
				fputs("\n",out);
			}
			break;
		case 2://last name
			for(i=0;i<numberNames;i++){
				for (j=i+1;j<numberNames;j++){
					if(strcmp(customers[i].last,customers[j].last)>0){
						*tempC=customers[i];
						customers[i]=customers[j];
						customers[j]=*tempC;
					}
				}
			}
			for(i=0;i<numberNames;i++){
				fputs(customers[i].first,out);
				fputs("\t",out);
				fputs(customers[i].last,out);
				fputs("\t",out);
				snprintf(temp,100,"%.2f",customers[i].total);
				fputs(temp,out);
				fputs("\n",out);
			}
			break;
		}
		free(customers);
		free(temp);
		fclose(names);
		fclose(purchs);
		fclose(out);
	}
	return 0;
}



