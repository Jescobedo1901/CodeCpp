/*
CMPS 3600
Escobedo Jacob
Lab 07
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <pthread.h>


struct BAT {
    int id;
    char dir;
};

//BATMAN monitor
struct BATMAN {

    //Mutex
    pthread_mutex_t mutex;
    int queue_count[4];
    //bool for crossing
    struct BAT* qFirst[4];
    //Who crosses
    struct BAT* crossing[4];
    pthread_cond_t queue[4];
    pthread_cond_t first[4];
    pthread_cond_t deadlockStatus;

    int passing[4];
    int running_count;
    int bat_count;
};

//Char to Int
int dirIndex(char c) {
    switch (tolower(c)) {
        case 'n':
            return 0;
        case 'w':
            return 1;
        case 's':
            return 2;
        case 'e':
            return 3;
        default:
            exit(1);
    }
}

//Int to Char
char indexDir(int val) {
    switch (val) {
        case 0: 
            return 'N';
        case 1: 
            return 'W';
        case 2: 
            return 'S';
        case 3: 
            return 'E';
        default:
            exit(1);
    }
}

//positive mod
int mod(int a, int b) {
    return (a + b) % b;
}

void arrive(struct BATMAN* man, struct BAT* b) {
    // code to check traffic in line, use counters, condition variables etc.
    pthread_mutex_lock(&man->mutex);
    int idx = dirIndex(b->dir);
    //join queue
    ++man->queue_count[idx]; 
    printf("BAT %d from %c arrives at crossing\n", b->id, toupper(b->dir));
    //Wait until first is available
    while(man->qFirst[idx] != NULL) {
        pthread_cond_wait(&man->queue[idx], &man->mutex);
    }
    //Take first spot
    man->qFirst[idx] = b;
    
    pthread_mutex_unlock(&man->mutex);    
    sleep(1);
}

void cross(struct BATMAN* man, struct BAT* b) {    
    pthread_mutex_lock(&man->mutex);        
    
    int idx = dirIndex(b->dir);
    int signalNext = mod(idx + 1, 4);
    
    //Who gets to cross
    man->crossing[idx] = b;

    //Wait while the first one waiting on the left goes
    while (man->crossing[signalNext] != NULL) {

        //Since the right side is busy
        pthread_cond_wait(&man->first[idx], &man->mutex);
    }    
    sleep(1); // it takes one second for a BAT to cross

    pthread_mutex_unlock(&man->mutex);
}

void leave(struct BATMAN* man, struct BAT* b) {
    // code to check traffic, use counters, condition variables etc.
    pthread_mutex_lock(&man->mutex);
    printf("BAT %d from %c leaving crossing\n", b->id, toupper(b->dir));

    int idx = dirIndex(b->dir);
    int signal_prev = mod(idx - 1, 4);

    //No longer apart of the queue
    --man->queue_count[idx];
    man->qFirst[idx] = NULL;
    man->crossing[idx] = NULL;
    //signal previous bat to go
    pthread_cond_signal(&man->first[signal_prev+1]);
    //Signal bat behind to take first spot
    pthread_cond_signal(&man->queue[idx]);
    --man->running_count;
    pthread_mutex_unlock(&man->mutex);
}

int is_running(struct BATMAN* man) {
    int count = 0;
    pthread_mutex_lock(&man->mutex);
    count = man->running_count;
    pthread_mutex_unlock(&man->mutex);
    return count;
}


void check(struct BATMAN* man) {
    // the manager checks for deadlock and resolves it
    pthread_mutex_lock(&man->mutex);
    //thread with queue and permission
    int incDir = 0;
    for(int i = 0; i < 4; ++i) {
        incDir += (man->qFirst[i] != NULL) && (!man->passing[i]);
    }
    //If all directions have a queue
    //and we haven't already given a direction a free pass
    //we are jammed
    int dir_to_signal = dirIndex('N');
    //if incDir all four sides, deadlock
    if(incDir == 4) {
        //If deadlock signal North
        printf("DEADLOCK: BAT jam detected, signaling North to go\n");
        //Gives BAts a sign that they can break out of waiting loop
        man->passing[dir_to_signal] = 1;        
        pthread_cond_signal(&man->first[dir_to_signal]);
        
    }
    //printf("Done Checking...\n");
    pthread_mutex_unlock(&man->mutex);
}

struct strctInitialize {
    struct BAT* bat;
    struct BATMAN* batman;
};

void* batfun(void* arg) {
    //Initialize structs for use in functions
    struct BAT* bat = ((struct strctInitialize*) arg)->bat;
    struct BATMAN* man = ((struct strctInitialize*) arg)->batman;
    free(arg);
    if (!bat) {
        printf("No bats for threads");
    } else {
        arrive(man, bat);
        cross(man, bat);
        leave(man, bat);
    }
    pthread_exit(NULL);
}

void testingFun(const char* testcase) {
    printf("tesing input: %s\n", testcase);
    struct BATMAN man;

    pthread_mutex_init(&man.mutex, NULL);

    pthread_cond_init(&man.deadlockStatus, NULL);
    
    //Initializez all situations
    for (int i = 0; i < 4; ++i) {
        man.queue_count[i] = 0;
        man.qFirst[i] = NULL;
        pthread_cond_init(&man.queue[i], NULL);
        pthread_cond_init(&man.first[i], NULL);
        man.passing[i] = 0;
        man.crossing[i] = NULL;
    }
    
    int nr_of_bats = strlen(testcase);
    if (nr_of_bats > 0) {

        pthread_t threads[nr_of_bats];
        struct BAT bats[nr_of_bats];
        man.bat_count = nr_of_bats;
        man.running_count = nr_of_bats;
        for (int i = 0; i < nr_of_bats; ++i) {
            bats[i].id = i + 1;
            bats[i].dir = testcase[i];

            struct strctInitialize* initthread = malloc(sizeof (struct strctInitialize));
            initthread->bat = &bats[i];
            initthread->batman = &man;
            pthread_create(&threads[i], NULL, &batfun, (void*) (initthread));
        }

        while(is_running(&man)) {
            check(&man);
        }

        for (int i = 0; i < nr_of_bats; ++i) {
            pthread_join(threads[i], NULL);
        }

    } else {
        printf("Input strength too short");
    }
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("Invalid argument, using test case\n");
        testingFun("neswwe");
    } 
    if (argc > 1) {
        testingFun(argv[1]);
    }
    //else {
        //testingFun(*argv);
    //    testingFun("neswwe");
    //}
    return 0;
}