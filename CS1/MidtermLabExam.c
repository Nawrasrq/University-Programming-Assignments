// Please read all the comments in this code for instruction
/* The announce lab exam policy applies to this lab exam.
The following piece of code creates a sorted linked list with 3, 4, 5, 6. A simplePrint function is used to print the data in the linked list. You can run and test the content of the linked list.

What you have to do:

There are two blank functions bellow that you should complete based on the requirements described as comments inside the function.
To test your function you may or may not need to uncomment/add lines in the main function. Compare your result with the comment given in main function.

After completing the code and testing, submit the modified file in webocurses before the due time.
Caution: No code will be accepted in email if you miss the deadline. Also do not share your code as sharing will be considered as dishonesty and will be treated accordingly.

Do not hard code to print just the numbers without really calculating it. Hard code will result in -10

                  Write your name here: Nawras Rawas Qalaji
                   your UCFID: na4970800

*/
#include<stdio.h>
#include<stdlib.h>
 typedef struct nod{
	int info;
	struct nod *next;
}node;

node* SortInsert(node *root, int item); //this function is complete
void simplePrint(node* root); //this function is complete
int sumMyList(node* root); //you have to write this function, see bellow //total grade 5
node* AddNToBelowM (node* root, int N, int M); //you have to write this function, see bellow //total grade 5

int main()
{
    node* head1=NULL;
	node* head2 = NULL;
	node* head3 = NULL;
	node* head4 = NULL;
	node *t;
	int ch,ele;
	head1 = SortInsert(head1, 4);
	head1 = SortInsert(head1,6);
	head1 = SortInsert(head1,3);
	head1 = SortInsert(head1,5);

    printf("\nSimple print List 1: ");
    simplePrint(head1);

	printf("\nsum of the list %d", sumMyList(head1)); //modify the sumMyList function to make it work. It should print 18.


	//call the AddNToBelowM function appropriately in next line. Pass N= 2 and M= 5);
	AddNToBelowM(head1,2,5);
	// write the call statement here
	printf("\nSimple print After AddNToBelowM: ");
    simplePrint(head1); // this should print 5 6 5 6 if your function is correct
	printf("\n");



	return 0;

}

void simplePrint(node* root)
{
    node* t=root;
    while(t!=NULL)
    {
        printf("%d ",t->info);
        t=t->next;
    }
}

node*  SortInsert(node* root, int item)
{
    node *temp;
    node *t;
    temp= (node *) malloc(sizeof(node));
    temp->info=item;
    temp->next=NULL;
    if (root==NULL || root->info >=item)
    {
            temp->next = root;
            root = temp;
    }
    else
    {
         t = root;
         while (t->next != NULL && t->next->info <item)
                   t = t->next;
         temp->next = t->next; //if the loop breaks for t->next == NULL, then temp next is becoming NULL too. So, no problem
         t->next = temp;
    }

    return root;
}

///////// All questions are starting here//////////////////



int sumMyList(node* root)
{		
	int result = root->info;
	node *head = root->next;
	
	while(head->next != NULL){
		result = result + head->info;
		head = head->next;
	}
	result = result + head->info;
	
	return result;
    /*this function takes the head of a linked list and return the sum of all the data in the linked list. If you use recursion, you will get full 5/5. If you use loop, you will get 4/5. If you are not confident about recursion, use loop first. If you have time after completing all the work, then try using recursion.*/
};


node* AddNToBelowM (node* root, int N, int M)
{
    /*this function takes the head of a linked list and two values N and M. Then it adds N to all the nodes that contian a data less than M
     For example, if we call this method with a linked list 3, 4, 5, 6 and if we call this method by AddNToBelowM (head, 2, 5),
     the the linked list will become 5, 6, 5, 6. At the end the function returns the root of the updated list*/
	 //start writing your code here
	 
	node *head = root;
	while(head->next != NULL){
		if(head->info < M){
			head->info = head->info + N;
		}
		head = head->next;
	}
	if(head->info < M){
			head->info = head->info + N;
		}
		head = head->next;
		
		
	return root;
}


