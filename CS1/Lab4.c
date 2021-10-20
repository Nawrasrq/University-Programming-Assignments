#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_SIZE 100

typedef struct Customer{
	int account_no;
	char name[100];
}customer;

struct queue{
	customer* customers;
	int front;
	int numElements;
	int queueSize;
};
void init(struct queue* qPtr);
void enqueue(struct queue* qPtr, customer val);
customer dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
int isFull(struct queue* qPtr);
int isEmpty(struct queue* qPtr);
void displayQueue(struct queue* qPtr);

int main(void){
	struct queue* callCenterQueue = (struct queue*)malloc(sizeof(struct queue));    
	init(callCenterQueue);
	customer input;
	customer* inputP = &input;
	
	char callOrServe[2] = {'c','s'};
	int random = 0;
	
	while(1 == 1){
		random = rand() % 2;
		if(callOrServe[random] == 'c'){
			printf("Making call!\n");
			if(isFull(callCenterQueue) == 1){
				printf("System has reached capacity, please call back later\n");
			}
			else{
				printf("input your first name\n");
				fflush(stdout);
				scanf("%s",inputP->name);
				printf("input your account number\n");
				scanf("%d",&inputP->account_no);
				enqueue(callCenterQueue, input);
				displayQueue(callCenterQueue);
			}
		}
		else if(callOrServe[random] == 's'){
			printf("Now serving!\n");
			if(isEmpty(callCenterQueue) == 1){
				printf("No customers in queue!\n");
			}
			else{
				printf("Customer %s has been served\n", dequeue(callCenterQueue).name);
				displayQueue(callCenterQueue);
			}
			
		}
	}
	return 1;
}

void init(struct queue* qPtr){
	qPtr->customers = (customer*)malloc(sizeof(int)*INIT_SIZE);
	qPtr->front = 0;
	qPtr->numElements = 0; 
	qPtr->queueSize = INIT_SIZE;
}

int isFull(struct queue* qPtr){
	if(qPtr->numElements == qPtr->queueSize){
		return 1;
	}
	else return 0;
}

int isEmpty(struct queue* qPtr){
	if(qPtr->numElements == 0){
		return 1;
	}
	else return 0;
	
}

void enqueue(struct queue* qPtr, customer val) {
	if(qPtr->numElements != qPtr->queueSize){
		qPtr->customers[qPtr->front] = val;
		(qPtr->numElements)++;
		qPtr->front = qPtr->front+1;
	}
	else{
		printf("Queue is full, dequeue first\n");
	}	
}

customer dequeue(struct queue* qPtr) {    
	customer retval;    

	retval = qPtr->customers[qPtr->front];    
	qPtr->front = (qPtr->front - 1);    
	(qPtr->numElements)--;     
	return retval;
}

int empty(struct queue* qPtr) {    
return qPtr->numElements == 0;
}

void displayQueue(struct queue* qPtr){
	int i;
	for(i=0;i<qPtr->numElements;i++){
		printf("Slot %d Customer: %s , ID: %d\n", i+1, qPtr->customers[i].name, qPtr->customers[i].account_no);
	}
}