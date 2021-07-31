#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>


void childProcess();

int main(int argc, char *argv[])
{
    int pid = fork();
    if(pid==0){
        childProcess();
    }  
}

void childProcess(){
    fork();
    fork();
    fork();
    printf("Print Parent: %d , Child: %d\n", getppid(), getpid());

}