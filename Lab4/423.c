#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>

#define CUSTOMER_NUMBER 1000
int serveCount = 0;
int number_of_chairs;
sem_t is_barber_sleeping;


void * runBarberShop(void* p_customer_id){
    int customer_id = *(int *)p_customer_id;
    if(number_of_chairs==0) return p_customer_id;
    else number_of_chairs--;
    
    printf("Customer %d is in the waiting room\n",customer_id);
    
    sem_wait(&is_barber_sleeping);
    number_of_chairs++;
    printf("Customer %d is gets served\n",customer_id);

    serveCount++;
    sem_post(&is_barber_sleeping);
    free(p_customer_id);
    
}

int main(int argc, char* argv[]){
   
    printf("Number of chairs?");
    scanf("%d",&number_of_chairs);

    pthread_t customers[CUSTOMER_NUMBER];
    sem_init(&is_barber_sleeping,0,1);

    for(int i =0; i<CUSTOMER_NUMBER; i++){
        int *p_customer_id = malloc(sizeof(int));
        *p_customer_id=i;
        if(pthread_create(&customers[i],NULL,&runBarberShop,p_customer_id)!=0){
            perror("FAILED THREAD CREATION");
        }
    }

    for(int i =0; i<CUSTOMER_NUMBER; i++){
       if(pthread_join(customers[i],NULL)!=0){
           perror("FAILED JOINING");
       }
    }

    printf("\nServed: %d Left: %d",serveCount,(CUSTOMER_NUMBER-serveCount));

    

    return 0;

}