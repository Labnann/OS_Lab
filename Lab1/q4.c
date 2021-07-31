#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>


void childProcess();
void parentProcess();
void input();
void bubbleSort(int numbers[], int size);
void printArray(int numbers[], int size);
int binarySearch(int numbers[], int left, int right, int value);

int size, array[1000], searchValue;

int main(int argc, char *argv[])
{
    input();
    int pid = fork();
    if(pid==0){
        childProcess();
    }  else parentProcess();
}

void childProcess(){
   bubbleSort(array,size);
   printArray(array,size);
}

void parentProcess(){
    wait(NULL);
    int searchResult = binarySearch(array,0,size-1,searchValue);
    if(searchResult>0) printf("The value %d is there! \n",searchValue);
    else printf("The value %d is NOT there. \n", searchValue);
    
}

void bubbleSort(int numbers[], int size){
    for(int i =0; i<size; i++){
        for(int j = 0; j<size-i-1; j++){
            if(numbers[j]>numbers[j+1]){
                int temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }

        }
    }

}

void input(){
    printf("Array size?\n");
    scanf("%d",&size);
    printf("Input array:\n");
    for(int i = 0; i<size; i++){
        scanf("%d",&array[i]);
    }

    printf("To search?\n ");
    scanf("%d",&searchValue);
}

void printArray(int numbers[], int size){
    for(int i = 0; i<size;i++){
        printf("%d ",numbers[i]);
    }
     printf("\n");
}

int binarySearch(int numbers[], int left, int right, int value)
{
   if (right >= left)
   {
        int mid = left + (right - left)/2;
        if (numbers[mid] == value)  return mid;
        if (numbers[mid] > value) return binarySearch(numbers, left, mid-1, value);
        return binarySearch(numbers, mid+1, right, value);
   }
   return -1;
}