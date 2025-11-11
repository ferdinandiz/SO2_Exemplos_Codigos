#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define PERIOD_MS 100   // período de 100 ms

static void busy_work(void) {
    // Simula algum trabalho pesado
    volatile double x = 0;
    for (int i = 0; i < 1000000; i++) {
        x += i * 0.000001;
    }
}

int main(void) {
    struct timespec next;
    clock_gettime(CLOCK_MONOTONIC, &next);

    for (int k = 0; k < 50; k++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        busy_work(); // "tarefa" que consome CPU

        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calcula tempo de execução
        long exec_ms = (end.tv_sec - start.tv_sec) * 1000 +
                       (end.tv_nsec - start.tv_nsec) / 1000000;

        printf("Instância %d executou em %ld ms\n", k, exec_ms);

        // Agenda próximo período
        next.tv_nsec += PERIOD_MS * 1000000;
        while (next.tv_nsec >= 1000000000L) {
            next.tv_nsec -= 1000000000L;
            next.tv_sec++;
        }

        // Dorme até o próximo instante planejado
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
    }

    return 0;
}
