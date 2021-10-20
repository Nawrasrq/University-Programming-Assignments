/*COP 3502C Final term Assignment One
This program is written by: Nawras Rawas Qalaji*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//global variable to store the filtered array's length
int filteredLength;

typedef struct coordinate{
	int x;
	int y;
}coordinate;


void readData(coordinate *a ,FILE *input ,int size){
	int i;
	for(i=0;i<size;i++){
		fscanf(input, "%d", &a[i].x);
		fscanf(input, "%d", &a[i].y);
		
	}
}

coordinate* filterData(coordinate *Array, int circleR, int size){
	int i,j = 0;
	double distance;
	
	//loops to find the size of the filtered array
	for(i = 0;i<size; i++){
		distance = sqrt(pow(Array[i].x,2) + pow(Array[i].y,2));
		if(distance <= (double)circleR){
			j=j+1;
		}
	}
	filteredLength = j;
	//creates newly sized filter array
	coordinate *filteredPoints = (coordinate*)malloc(filteredLength*sizeof(coordinate));	
	//loops again assigning filtered points to the new array
	for(i = 0,j=0;i<size; i++){
		distance = sqrt(pow(Array[i].x,2) + pow(Array[i].y,2));
		if(distance <= (double)circleR){
			filteredPoints[j] = Array[i];
			j=j+1;
		}
	}
	return filteredPoints;
}

void merge(coordinate *array, int beg, int mid, int end){ 
    int i, j, k; 
    int n1 = mid - beg + 1; 
    int n2 =  end - mid; 
	
	//left sub array and Right sub array
    coordinate L[n1], R[n2]; 
  
    for(i = 0; i < n1; i++){ 
        L[i] = array[beg + i]; 
	}
    for(j = 0; j < n2; j++){
        R[j] = array[mid + 1+ j];
	}
    i = 0, j = 0;  
    k = beg;
	while(i < n1 && j < n2){ 
        if(L[i].x < R[j].x){ 
            array[k] = L[i]; 
            i++; 
        } 
        else if(L[i].x > R[j].x){ 
            array[k] = R[j]; 
            j++; 
        } 
		else{
			if(L[i].y < R[j].y){ 
				array[k] = L[i]; 
				i++; 
			}
			else{
				array[k] = R[j]; 
				j++;				
			}
        } 
        k++; 
    } 
  
    while(i < n1){ 
        array[k] = L[i]; 
        i++; 
        k++; 
    } 
    while(j < n2){ 
        array[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void mergeSort(coordinate *array, int beg, int end){ 
    if (beg < end){ 
        int mid = beg+(end-beg)/2; 
  
        mergeSort(array, beg, mid); 
        mergeSort(array, mid+1, end); 
        merge(array, beg, mid, end);
	}
}

int binarySearch(coordinate *array ,coordinate input, int beg, int end){ 
    if(end >= beg){ 
        int mid = beg + (end - beg) / 2; 
        
		if(array[mid].x == input.x && array[mid].y == input.y){			
            return mid; 
		}
		
        if(array[mid].x >= input.x){
            return binarySearch(array, input, beg, mid - 1); 
		}
        else{
			return binarySearch(array, input, mid + 1, end);
		} 
    } 
    return -1; 
} 

void searchPhase(coordinate *array){
	coordinate input;
	int a;
	int record;
	
	while(input.x != 999 || input.y != 999){
		printf("Search input (x y): ");
		scanf("%d %d",&input.x,&input.y);
		
		record = binarySearch(array,input,0,filteredLength);
		if(input.x == 999 || input.y == 999){
			printf("Output: exit\n");
			break;
		}
		else if(record != -1){
			printf("Output: Found at record %d\n", record+1);
		}
		else
			printf("Output: Not found\n");
	}
	
}

int main(void){
	FILE *fp, *outfp;
	int circleR, NLines;
	int i;
	
	coordinate center;
	fp = fopen("in.txt", "r");
	outfp = fopen("out.txt", "w");
	
	//scanning first line of in.txt for center coordinate, radius and Nlines
	readData(&center, fp,1);
	fscanf(fp, "%d", &circleR);
	fscanf(fp, "%d", &NLines);
	
	//creates a new array using NLines for size
	coordinate *pointsArray = (coordinate*)malloc(NLines*sizeof(coordinate));	
	
	//fills new array with all the points read from in.txt
	readData(pointsArray, fp, NLines);
	
	//filters points outside of the circle using the distance formula
	pointsArray = filterData(pointsArray, circleR, NLines);
	
	//sorts the arrays
	mergeSort(pointsArray,0,filteredLength);
	
	//write out.txt file and close the opended files
	for(i=0; i < filteredLength;i++){
		fprintf(outfp,"%d %d\n",pointsArray[i].x, pointsArray[i].y);
	}
	fclose(fp);
	fclose(outfp);
	
	//begins the searchPhase
	printf("Filtered and sorted data written to out.txt\n");
	searchPhase(pointsArray);
}