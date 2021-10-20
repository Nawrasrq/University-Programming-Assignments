/*COP 3502C Midterm Assignment One
This program is written by: Nawras Rawas Qalaji*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define max_size 50


int isOperator(char c){
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^'){ return 1; }
	else return 0;
}

int getOperatorPriority(char c){ //4 is high 1 is low
	if(c == '+' || c == '-'){ return 2; }
	else if(c == '*' || c == '/' || c == '%'){ return 3; }
	else if(c == '^'){ return 4; }
	else return 1;
}


char POP(char *stack,int *top){
	char temp;
	if(*top < -1){
		printf("stack underflow\n");
		return -1;
	}
	else{
		temp = stack[*top];
		*top=*top-1;
    return temp;
	}
}

int POPint(int *stack,int *top){
	int temp;
	if(*top < -1){
		printf("stack underflow\n");
		return -1;
	}
	else{
    temp = stack[*top];
   *top=*top-1;
		return temp;
	}
}

void push(char *stack, int *top, char x){
	if(*top >= max_size){
		printf("stack overflow\n");
	}
	else {
    *top = *top + 1;
		stack[*top] = x;
	}
}

void pushint(int *stack, int *top, int x){
	if(*top >= max_size){
		printf("stack overflow\n");
	}
	else {
    *top = *top + 1;
		stack[*top] = x;
	}
}

int isBalancedParenthesis(char *input){
	char stack[max_size];
	int i,top = -1; 
	char a;
	char *b = &a;
 
	for(i=0;i<input[i];i++){
		if(input[i] == '('){ push(stack,&top,input[i]); }
		else if(input[i] == ')'){
					if(input[i] != '(' ){ 
						a = POP(stack,&top);          
				  }       
	   }
  }
    if(top == -1){ return 1; }
	  else{ return 0; }
}
int calculate(int a, int b, char op){
	int i,result;
  switch(op){
	case '^':
    result = a;
		for(i=1;i<b;i++){
      result*=a;
    }
    return result;
    break;
	case '*':
 //   printf("multiply %d\n", a*b);
		return a*b;
    break;
	case '/':
	//	printf("divide %d\n", a/b);
    return a/b;
    break;
	case '%':
   // printf("module %d\n", a%b);
		return a%b;
    break;
	case '+':
   // printf("addition %d\n", a+b);
		return a+b;
    break;
	case '-':
  //  printf("subtraction %d\n", a-b);
		return a-b;
    break;
	default:
  //  printf("default");
		return -1;
    break;
	} 
}

int convertToInt(char *c, int start){
	
  int i,dec = 0;
  
  for(i=start; isdigit(c[i]); i++){
     dec = dec * 10 + (c[i] - '0');
  }
  return dec;
}

char* convertToPostFix(char *input){
	char *stack = (char*)malloc(strlen(input)* sizeof(char));
	char *postfix = (char*)malloc(strlen(input)* sizeof(char));
	int i,j =0,top = -1;
	char a;
	char *b = &a;
   
		for(i=0;input[i];i++){
      if(isdigit(input[i])){
				a = input[i];
				strncat(postfix,b,1);
        
        if(!isdigit(input[i+1])){
          a = ' ';
          strncat(postfix,b,1);
        }
 			}
      
			else if(input[i] == '('){
					push(stack,&top,input[i]);   
   		}
      
			else if(input[i] == ')'){
			  while(stack[top] != '(' && top > -1){
          a = POP(stack,&top);
					strncat(postfix,b,1);
          a = ' ';
          strncat(postfix,b,1);
          }
          a = POP(stack,&top);
       }
      
			else if(isOperator(input[i]) == 1){
          
        while(top >= -1 && getOperatorPriority(input[i]) <= getOperatorPriority(stack[top])){ 
          a = POP(stack,&top);
          strncat(postfix, b,1);
          a = ' ';
          strncat(postfix,b,1);
        }
      if(getOperatorPriority(input[i]) > getOperatorPriority(stack[top]) || top <=-1){ push( stack, &top, input[i]); }
       }
  } 
  for(i=-1;i<=top;i++){
    if(stack[top] != '('){
      a = POP(stack,&top);
      strncat(postfix, b,1); 
      a = ' ';
      strncat(postfix,b,1);
    }
  }	 
	return postfix;
}

void evaluate(char *postfix){
	int stack[max_size];
	int j,i = 0;
  int top = -1; 
	int val1 =0;
  int val2 = 0;
  
  for(i = 0; postfix[i]; i++){
      if(isdigit(postfix[i])){
        pushint(stack, &top, convertToInt(postfix,i));
    
        for(j=i;isdigit(postfix[j]);j++){}
        j=j-i;
        i=i+j; 
    
		  }
  
		else if(isOperator(postfix[i]) == 1){  
     val1 = POPint(stack, &top);
     val2 = POPint(stack, &top);
		 pushint(stack, &top, calculate(val2,val1,postfix[i]));
		}
	}
	printf("value: %d\n", POPint(stack, &top));
}

char* menu(){
  char *input =(char*)malloc(max_size * sizeof(char));
  printf("e for entering an infix, x for exiting the program\n");
  scanf("%s",input);
  
  if(strcmp(input,"x")==0){
  free(input);
  return "exit";
  }
  else{
  free(input);
  return input;
  }
}

int main(void){
	char *input = (char*)malloc(max_size * sizeof(char));
	char *select = (char*)malloc(max_size * sizeof(char));
  char *postfix = (char*)malloc(max_size * sizeof(char));
  
  while(strcmp(select = menu(), "exit" )!=0){
    fgets(input,max_size,stdin); 
    fgets(input,max_size,stdin);
    
    printf("infix: %s", input);
    
    if(isBalancedParenthesis(input) == 1){
      printf("parenthesis: balanced\n");
      postfix = convertToPostFix(input);
      printf("postfix: %s\n", postfix);
      evaluate(postfix);
    }
    else{
      printf("parenthesis: imbalanced\n");
      printf("postfix: n/a\n");
      printf("value: n/a\n");
    }
    free(select);
    free(input);
    free(postfix);
  }
  return 0;
}
