#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>


void childProcess();
void parentProcess();

int variable = 0;

int main(int argc, char *argv[])
{

    int pid = fork();
    if(pid==0){
        childProcess();
        wait(NULL);
    }
      
     parentProcess();
}

void childProcess(){
    variable+=180042133;
    printf("Variable from child process: %d \n",variable);

    
}

void parentProcess(){
   
     variable+=133;
    printf("Variable from parent process: %d \n",variable);

}