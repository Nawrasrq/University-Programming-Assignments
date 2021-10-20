/*written by: Nawras Rawas Qalaji*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

FILE *fp, *outfp;
int N;
int topIncome = 0;
int totalCount = 0;
int totalIncome = 0;
int singleChildren = 0;

typedef struct tree_node {  
	int income;  
	int count;
	struct tree_node *left;  
	struct tree_node *right;
}tree_node;

tree_node* insert(tree_node *root, tree_node *element){
	
	if(root == NULL){
		return element;
	}	
	if(element->income < root->income){
		root->left = insert(root->left, element);
	}
	else if(element->income > root->income){
		root->right = insert(root->right, element);
	}
	return root;
}


tree_node* createNode(int income, int count){
	tree_node *temp;
	temp = (tree_node*)malloc(sizeof(tree_node));
	
	temp->income = income;
	temp->count = count;
	
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void inorder(tree_node *root){
	if(root != NULL){
		inorder(root->left);
		printf("(%d, %d)",root->income,root->count);
		fprintf(outfp,"(%d, %d)",root->income,root->count);
		inorder(root->right);
	}
}
void highestIncome(tree_node *root){
	if(root != NULL){
		if(topIncome < root->income){
			topIncome = root->income;
			totalCount = root->count;
		}
		
		highestIncome(root->left);
		highestIncome(root->right);
	}
}
void countSolo(tree_node *root){
	if(root != NULL){
		countSolo(root->left);
		if(root->right == NULL && root->left != NULL ||root->right != NULL && root->left == NULL){
			singleChildren = singleChildren + 1;
		}
		countSolo(root->right);
	}
}

void calculateTotal(tree_node *root){
	if(root != NULL){
		
		calculateTotal(root->left);
		totalIncome = totalIncome + (root->income * root->count);
		
		calculateTotal(root->right);
	}
}
	

int main(void){
	fp = fopen("in.txt", "r");
	outfp = fopen("out.txt", "w");
	fscanf(fp, "%d", &N);

	int i,j,Scount,Sincome;
	
	fscanf(fp, "%d", &Sincome);
	fscanf(fp, "%d", &Scount);
	
	tree_node *root = createNode(Sincome,Scount);

	for(i=0;i<N;i++){

		fscanf(fp, "%d", &Sincome);
		fscanf(fp, "%d", &Scount);
		insert(root, createNode(Sincome,Scount));
	}
	fprintf(outfp, "Tree constructed from the file\n");
	fprintf(outfp, "In-order: ");
	
	
	printf("Tree constructed from the file\n");
	printf("In-order: ");
	inorder(root);
	printf("\n");
	fprintf(outfp, "\n");
	
	highestIncome(root);
	printf("Highest income: %d Total people with highest income: %d\n", topIncome, totalCount);
	fprintf(outfp, "Highest income: %d Total people with highest income: %d\n", topIncome, totalCount);
	
	countSolo(root);
	printf("Total single children in the tree: %d\n", singleChildren);
	fprintf(outfp, "Total single children in the tree: %d\n", singleChildren);
	
	calculateTotal(root);
	printf("Total income in the area: %d\n", totalIncome);
	fprintf(outfp, "Total income in the area: %d\n", totalIncome);
	
	fclose(fp);
	fclose(outfp);
}