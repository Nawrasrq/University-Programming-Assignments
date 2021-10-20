/*COP 3502C Midterm Assignment two
This program is written by: Nawras Rawas Qalaji*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct soldier{
	int sequence;
	struct soldier *previous;
	struct soldier *next;
}soldier;

soldier* create_soldier(int sequence){
	soldier *node = (soldier*)malloc(sizeof(soldier));
	node->sequence = sequence;
	return node;
}

soldier* create_reserve_circle(int n){	
	int i;
	soldier *node;
	soldier *head;
	soldier *prev;
	
	node = create_soldier(n);
	head = node;
 
	for(i=n-1;i>=1;i--){
		prev = node;
		node->next = create_soldier(i);
    node = node->next;
    node->previous = prev;
	}
	prev = node;
  node->next = head;
  head->previous = prev;
	return head;
}

soldier* rearrange_circle(soldier* head){
	soldier *last = head->previous;
	soldier *next;
	soldier *prev;
	soldier *curr;
   
  while(curr != last){
    next = head->next;
    curr = head;
    prev = head->previous;
    head = head->next;
    
    curr->next=prev;
    curr->previous=next;
  }
  head = last;
	return head;
}

void display(soldier* head){
	int a = head->sequence; 
	printf("%d ",a);
	head = head->next;
	
	while(a != head->sequence){
		printf("%d ",head->sequence);
		head = head->next;
	}
	printf("\n");
	
}

soldier* deletion(soldier* head){
  soldier *prev = head->previous;
  soldier *next = head->next;
  
  free(head);
  head = next;
  head->previous = prev;
  prev->next = head;
}

int kill(soldier *head, int n, int k){
  int i,j;
  head=head->previous;
 for(i=0;i<n-1;i++){
 
   for(j=0;j<k;j++){
     head=head->next;
   }
   deletion(head);
 }
   head = head->next; 
 return head->sequence;
}

int main(void){
	int n,k;
	soldier *head;
	printf("input n k\n");
	
	scanf("%d %d",&n ,&k);
	head = create_reserve_circle(n);
	printf("List: ");
  display(head);
	
  printf("After ordering: ");
  head = rearrange_circle(head);
  display(head);
  
  printf("Survived: %d\n", kill(head, n, k));
}