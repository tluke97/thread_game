#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


#define THREAD_COUNT 5

void * fighty_boi (void *arg);
void * jackass_friends(void *arg);

int bad_things;
struct thread_data {
    long timer;
    int items;
};
struct thread_data t_d[5];
pthread_barrier_t barr;

int main(int argc, char **argv)
{

    pthread_t me, rylee, haley, ryann, swift;
    pthread_t threads[5] = {me, rylee, haley, ryann, swift};
    struct thread_data me_d, rylee_d, haley_d, ryann_d, swift_d;
    //t_d = {me_d, rylee_d, haley_d, ryann_d, swift_d};
    t_d[0] = me_d;
    t_d[1] = rylee_d;
    t_d[2] = haley_d;
    t_d[3] = ryann_d;
    t_d[4] = swift_d;
    bad_things = 0;
    srand(time(NULL));

    if(pthread_barrier_init(&barr, NULL, THREAD_COUNT))
    {
        printf("Could not create a barrier\n");
        return -1;
    }

    for (int i = 0; i < THREAD_COUNT; i++) {

        void* func;

        if (i == 0) {
            func = &fighty_boi;
        } else {
            func = &jackass_friends;
        }

        if(pthread_create(&threads[i], NULL, func, (void *)(&i)))
        {
            printf("Could not create thread\n");
            return -1;
        }

        if(pthread_join(threads[i], NULL))
        {
            printf("Could not join thread\n");
            return -1;
        }


    }



    return 0;
}



void * fighty_boi (void *arg) {
    printf("i'm a fighter boo ya \n");



    return NULL;
}

void * jackass_friends(void *arg) {
    while (1) {
        struct timeval stop, start;
        gettimeofday(&start, NULL);
        int i = *(int*)arg;
        struct thread_data thread_d = t_d[i];

        if (thread_d.timer >= 1000) {
            int rand_num = rand() % 10;
            if (rand_num == 0) {
                printf("Im going to let something in!!!!!!!!!!!!!!!!!!!\n");
                thread_d.items += 1;
            }
            //reset the 10ms timer
            thread_d.timer = 0;
        }

        gettimeofday(&stop, NULL);
        long time_taken = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
        printf("took %lu us\n", time_taken);
        thread_d.timer += time_taken;
    }
    return NULL;
}



