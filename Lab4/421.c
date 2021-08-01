#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define PHILOSOPHER_COUNT 5

#define PHILOSOPHER_THINKING 1
#define PHILOSOPHER_EATING 2

#define CHOPSTICK_AVAILABLE 0
#define CHOPSTICK_UNAVAILABLE 1
#define TOTAL_CHOPSTICKS  4

sem_t eatingQuota;
sem_t chopstick_semaphores[PHILOSOPHER_COUNT-1];

int philosopher_states[5] = {0};

void *doPhilosophing(void *p_philosopher_id)
{

    while (1)
    {
        //WILLIAM STALLING
        //
        int current_philosopher_id = *(int *)p_philosopher_id;
        sem_wait(&eatingQuota);

      
        printf("Philosopher %d is Picking the forks\n", current_philosopher_id);
        sem_wait(&chopstick_semaphores[current_philosopher_id]);
        printf("Philosopher %d is Piced up the left fork\n", current_philosopher_id);
        sem_wait(&chopstick_semaphores[(current_philosopher_id+1)%(PHILOSOPHER_COUNT)]);
        printf("Philosopher %d is Piced up the right fork\n", current_philosopher_id);

         printf("Philosopher %d is Eating\n", current_philosopher_id);

        sem_post(&chopstick_semaphores[current_philosopher_id]);
        sem_post(&chopstick_semaphores[(current_philosopher_id+1)%(PHILOSOPHER_COUNT)]);

        sem_post(&eatingQuota);

    
         printf("PHILOSOPHER %d is thinking\n", current_philosopher_id);
        
    }
}

int main(int argc, char *argv[])
{
    pthread_t philosophers[PHILOSOPHER_COUNT];

    sem_init(&eatingQuota, 0, PHILOSOPHER_COUNT - 1);

    for(int i=0; i<5; i++){
        sem_init(&chopstick_semaphores[i],0,1);
    }

    for (int i = 0; i < PHILOSOPHER_COUNT; i++)
    {
        int *p_philospher_id = malloc(sizeof(int));
        *p_philospher_id = i;
        if (pthread_create(&philosophers[i], NULL, &doPhilosophing, p_philospher_id) != 0)
        {
            perror("FAILED THREAD CREATION");
        }
    }

    for (int i = 0; i < PHILOSOPHER_COUNT; i++)
    {
        if (pthread_join(philosophers[i], NULL) != 0)
        {
            perror("FAILED JOINING");
        }
    }

    return 0;
}



