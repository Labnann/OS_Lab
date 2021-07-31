#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>


void childProcess();
void parentProcess();
int fibonacci(int n);
void input();
void printSeries();

int numbers = 0;

int main(int argc, char *argv[])
{
    input();
    int pid = fork();
    if(pid==0){
        childProcess();
    }  else parentProcess();
}

void childProcess(){
    printSeries();
}

void parentProcess(){
    wait(NULL);
}

void printSeries(){
    int i;
    for(i =0; i<numbers; i++)
    printf("%d ",fibonacci(i));
    printf("\n");

}


int fibonacci(int n){
    if (n==0) return 0;
    if (n==1) return 1;
    else{
        return fibonacci(n-1) +fibonacci(n-2);
    }
}

void input(){
    printf("How many numbers in the fibonacci sequence to be calculated? \n");
    scanf("%d",&numbers);
    while (numbers<0){
        printf("Wrong Input, try again.\n");
        scanf("%d",&numbers);
    }
    
}