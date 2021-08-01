#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define PHILOSOPHER_COUNT 5

#define PHILOSOPHER_THINKING 1
#define PHILOSOPHER_EATING 2

#define CHOPSTICK_AVAILABLE 0
#define CHOPSTICK_UNAVAILABLE 1

sem_t semaphore;

int philosopher_states[5] = {0};
int chopstick_status[5] = {0};

void *routine(void *p_philosopher_id)
{

    while (1)
    {

        sem_wait(&semaphore);
        int current_philosopher_id = *(int *)p_philosopher_id;

        if (chopstick_status[current_philosopher_id] == CHOPSTICK_AVAILABLE && chopstick_status[(current_philosopher_id + 1) % PHILOSOPHER_COUNT] == CHOPSTICK_AVAILABLE)
        {
            chopstick_status[current_philosopher_id] = CHOPSTICK_UNAVAILABLE;
            chopstick_status[(current_philosopher_id + 1) % PHILOSOPHER_COUNT] = CHOPSTICK_UNAVAILABLE;

            printf("Philosopher %d is Eating\n", current_philosopher_id);

            chopstick_status[current_philosopher_id] = CHOPSTICK_AVAILABLE;
            chopstick_status[(current_philosopher_id + 1) % PHILOSOPHER_COUNT] = CHOPSTICK_AVAILABLE;
        }

        printf("PHILOSOPHER %d is thinking\n", current_philosopher_id);
        sem_post(&semaphore);
    }
}

int main(int argc, char *argv[])
{
    pthread_t philosophers[PHILOSOPHER_COUNT];

    sem_init(&semaphore, 0, PHILOSOPHER_COUNT - 1);

    for (int i = 0; i < PHILOSOPHER_COUNT; i++)
    {
        int *p_philospher_id = malloc(sizeof(int));
        *p_philospher_id = i;
        if (pthread_create(&philosophers[i], NULL, &routine, p_philospher_id) != 0)
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