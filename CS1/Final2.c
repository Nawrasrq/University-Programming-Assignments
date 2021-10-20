/*COP 3502C Final term Assignment two
This program is written by: Nawras Rawas Qalaji*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int N,S,D;
int totalChar = 0;
int itemsBefore = 0;
FILE *fp, *outfp;

typedef struct tree_node {  
	char name[10];  
	struct tree_node *left;  
	struct tree_node *right;
}tree_node;

int max(int left, int right){ 
    if(left >=  right){
		return left;
	}
	else return right;
}

int height(tree_node* root){ 
    if(root == NULL){ return 0; }	
	return 1 + max(height(root->left), height(root->right)); 
} 
int isBalanced(tree_node *root){
	int leftHeight, rightHeight;
	if(root == NULL){
		return 1;
	}
	leftHeight = height(root->left);
	rightHeight = height(root->right);
	
	if(abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)){
		return 1;
	}
	else{
		return 0;
	}
}

tree_node* createNode(char newName[]){
	tree_node *temp;
	temp = (tree_node*)malloc(sizeof(tree_node));
	
	strcpy(temp->name, newName);
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

tree_node* insert(tree_node *root, char newName[]){
	
	if(root == NULL){
		return createNode(newName);
	}
	
	if(strcmp(newName,root->name) < 0){
		root->left = insert(root->left, newName);
	}
	else if(strcmp(newName,root->name) > 0){
		root->right = insert(root->right, newName);
	}
	return root;
}

void preorder(tree_node *root){
	if(root != NULL){
		fprintf(outfp,"%s ",root->name);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(tree_node *root){
	if(root != NULL){
		inorder(root->left);
		fprintf(outfp,"%s ",root->name);
		inorder(root->right);
	}
}
void postorder(tree_node *root){
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		fprintf(outfp,"%s ",root->name);
	}
}
void totalCharacters(tree_node *root){
	if(root != NULL){
		totalChar = totalChar + strlen(root->name); 
		totalCharacters(root->left);
		totalCharacters(root->right);
	}
}	
void countBefore(tree_node *root, char searchKey[]){
	if(root != NULL){
		if(strcmp(root->name,searchKey) == 0){
			fprintf(outfp,"%s: Found, items before: %d\n",searchKey,itemsBefore);
		}
		else if(strcmp(searchKey,root->name) < 0){
			itemsBefore = itemsBefore + 1;
			countBefore(root->left,searchKey);
		}
		else{
			itemsBefore = itemsBefore + 1;
			countBefore(root->right,searchKey);
		}
	}
	else
		fprintf(outfp,"%s: Not found, items before: 0\n",searchKey); 
}
tree_node* smallestNode(tree_node *a){
	tree_node *current = a;
	while (current->left != NULL){ 
        current = current->left;
	}
	return current;
}

tree_node* delete(tree_node *root, char name[]){
	if(root == NULL){
		return root;
	}
	//search left side
	if(strcmp(name,root->name) < 0){
		root->left = delete(root->left, name);
	}
	//search right side
	else if(strcmp(name,root->name) > 0){
		root->right = delete(root->right, name);
	}
	//name is current root 
	else if(strcmp(name,root->name) == 0){
		//node has no children
		if(root->right == NULL){
			tree_node *temp = root->left;
			free(root);
			return temp;
		}
		
		//node has one child
		else if(root->left == NULL){
			tree_node *temp = root->right;
			free(root);
			return temp;
		}
		//if node has two children
		else{
			tree_node *temp = smallestNode(root->right);
			strcpy(root->name, temp->name);
			root->right = delete(root->right,temp->name);
		}
	}
	return root;
}

int main(void){	
	fp = fopen("input.txt", "r");
	outfp = fopen("out.txt", "w");

	int i,j;
	char scanned[10];
	tree_node *root;
	tree_node *head = root;
	
	fscanf(fp, "%d", &N);
	fscanf(fp, "%d", &S);
	fscanf(fp, "%d", &D);
	
	fscanf(fp,"%s",scanned);
	root = createNode(scanned);
	for(i=0;i<N;i++){
		fscanf(fp, "%s", scanned);
		insert(root, scanned);
	}
	fprintf(outfp,"Pre order: ");
	preorder(root);
	fprintf(outfp,"\nIn order: ");
	inorder(root);
	fprintf(outfp, "\nPost order: ");
	postorder(root);
	
	totalCharacters(root);
	fprintf(outfp,"\nTotal characters: %d", totalChar);	
	//print heights
	fprintf(outfp, "\nHeight left = %d, ", height(root->left)-1);
	fprintf(outfp, "Height right = %d, ", height(root->right)-1);
	//check for balance
	if(isBalanced(root) == 1){ fprintf(outfp, "The tree is balanced\n");}
	else{ fprintf(outfp,"The tree is imbalanced.\n");}
	fprintf(outfp, "Search Phase: \n");
	for(i=0;i<S;i++){
		itemsBefore = 0;
		countBefore(root,scanned);
		fscanf(fp, "%s", scanned);
	}
	
	fprintf(outfp, "Delete Phase: \n");
	for(i=0;i<D-1;i++){
		fprintf(outfp, "%s: deleted\n", scanned);
		delete(root,scanned);
		fscanf(fp, "%s", scanned);
	}
	fprintf(outfp, "%s: deleted\n", scanned);
	delete(root,scanned);
	fprintf(outfp, "In Order: ");
	inorder(root);
	//reset total characters global
	totalChar = 0;
	totalCharacters(root);
	fprintf(outfp, "\nTotal characters: %d\n", totalChar);	
	fclose(fp);
	fclose(outfp);
}