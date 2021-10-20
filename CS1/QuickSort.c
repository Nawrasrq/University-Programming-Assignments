/*COP 3502C Midterm Assignment One
This program is written by: Nawras Rawas Qalaji*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int partition(int arr[], int beg, int end){ 
    int x = arr[end];
	int i = beg; 
	int j;
    int temp;
	
	for (j = beg; j <= end-1; j++) { 
        if (arr[j] <= x){ 
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp; 
            i++; 
        } 
    }
	temp = arr[i];
	arr[i] = arr[end];
	arr[end] = temp; 
    return i; 
}
int kthSmallest(int arr[], int beg, int end, int k){ 
   if (k>0 && k <= end-beg+1) { 
  
        int index = partition(arr, beg, end); 
  
        if (index-beg == k-1){ 
            return arr[index]; 
		}
        if (index-beg > k-1){
			return kthSmallest(arr, beg, index-1, k);
		}  
		return kthSmallest(arr, index+1, end,k-index + beg-1); 
    }
    return -1; 
} 
  
int main(){
    int size;
	int i;
	int k;
	printf("Input size of array\n");
	scanf("%d", &size);
	
	int arr[size];	
	printf("Input each element one at a time\n");
	for(i=0;i<size;i++){
		scanf("%d", &arr[i]);
	}
	
	printf("Input kth element\n");
	scanf("%d", &k);
	
	int n = sizeof(arr) / sizeof(arr[0]);
	int result = kthSmallest(arr, 0, n - 1, k);
	
	
	if(result != -1){
		printf("%d is the kth smallest element\n ", result); 
    }
	else 
		printf("k is greater than the number of elements\n");
	return 0; 
} 
