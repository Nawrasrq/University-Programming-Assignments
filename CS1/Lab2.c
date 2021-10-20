#include <stdio.h>
#include <stdlib.h>
 
typedef struct students {
  char lastname[20];
  int assignment;
  int quizzes[];
  int finalexam;
  int total;
  }students;
  
students* readData(FILE *in, int *noOfRecords, int *noofquiz){


	int temptotal=0;
	int i,j,studentWhighscore;
	int highestScore = 0;
	
	FILE *op = fopen("output.txt","w");
  
  students *student = (students*)malloc(*noOfRecords * sizeof(students));
	
	for(i = 0; i< *noOfRecords;i++){
		student[i].quizzes* = (int*)malloc(*noofquiz * sizeof(int));
		
		fscanf(in,"%s ",student[i].lastname);
		fscanf(in,"%d ",&student[i].assignment);
    temptotal = temptotal + student[i].assignment;
		
		for(i = 0; j < *noofquiz;j++){
		fscanf(in,"%d ",&student[i].quizzes[j]);
		temptotal = temptotal + student[i].quizzes[j];
		}
		
		fscanf(in,"%d",&student[i].finalexam);
		temptotal = temptotal + student[i].finalexam;
		student[i].total = temptotal;
		
		if(student[i].total > highestScore){
			highestScore = student[i].total;
			studentWhighscore = i;
		}
		temptotal = 0;
	}
	fprintf(op, "Name: %s \nAssignment: %d\n Quizzes: ", student[studentWhighscore].lastname,student[studentWhighscore].assignment);
 
	printf("Name: %s \nAssignment: %d\n Quizzes: ", student[studentWhighscore].lastname,student[studentWhighscore].assignment);

	for(i = 0; i < *noofquiz;i++){
		fprintf(op, "%d ", student[studentWhighscore].quizzes[i]);
		printf("%d ", student[studentWhighscore].quizzes[i]);	
	}

	fprintf(op, "Final exam: %d\nTotal: %d\n", student[studentWhighscore].finalexam,student[studentWhighscore].total);
	
  printf("Final exam: %d\nTotal: %d\n", student[studentWhighscore].finalexam,student[studentWhighscore].total);
	
	fclose(in);
	fclose(op);
 return student;
}  
int main(){
 
  int noOfRecords, noofquiz;
  
  FILE *in = fopen("input.txt","r");
  fscanf(in,"%d %d",&noOfRecords, &noofquiz);
  readData(in, &noOfRecords, &noofquiz);


}

