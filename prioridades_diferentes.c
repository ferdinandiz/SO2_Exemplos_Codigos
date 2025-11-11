#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

void* high_prio_task(void* arg) {
    while (1) {
        printf("[HIGH] executando...\n");
        // simula trabalho
        for (volatile long i = 0; i < 10000000; i++);
        usleep(10000); // 10 ms
    }
    return NULL;
}

void* low_prio_task(void* arg) {
    while (1) {
        printf("   [LOW] executando...\n");
        for (volatile long i = 0; i < 10000000; i++);
        usleep(10000);
    }
    return NULL;
}

int main(void) {
    pthread_t th_high, th_low;
    pthread_attr_t attr_high, attr_low;
    struct sched_param param_high, param_low;

    pthread_attr_init(&attr_high);
    pthread_attr_init(&attr_low);

    // Define política de escalonamento em tempo real
    pthread_attr_setschedpolicy(&attr_high, SCHED_FIFO);
    pthread_attr_setschedpolicy(&attr_low,  SCHED_FIFO);

    // Altas prioridades numéricas = maior prioridade lógica
    param_high.sched_priority = 80;
    param_low.sched_priority  = 10;

    pthread_attr_setschedparam(&attr_high, &param_high);
    pthread_attr_setschedparam(&attr_low,  &param_low);

    pthread_attr_setinheritsched(&attr_high, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr_low,  PTHREAD_EXPLICIT_SCHED);

    if (pthread_create(&th_high, &attr_high, high_prio_task, NULL) != 0) {
        perror("pthread_create high");
        exit(1);
    }

    if (pthread_create(&th_low, &attr_low, low_prio_task, NULL) != 0) {
        perror("pthread_create low");
        exit(1);
    }

    pthread_join(th_high, NULL);
    pthread_join(th_low, NULL);
    return 0;
}
