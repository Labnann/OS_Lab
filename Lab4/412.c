#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


void myTurn(void *arg){
    for(int i = 0; i<10; i++)
    {
       sleep(1);
       printf("Turn of 1\n");
    }
    return NULL;
    
}

void yourTurn(){
    for(int i = 0; i<3; i++)
    {
        sleep(1);
        printf("Turn of 2\n");
    }
    
}

void main(){
    pthread_t newthread;

    pthread_create(&newthread,NULL,myTurn,NULL);
    //myTurn();
    yourTurn();
    pthread_join(newthread,NULL);
}