#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 5

int sum = 0;
void * runner(void * param);

int main(int argc, char * argv[]) {
    pthread_t tid[NUM_THREAD];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i=0; i<NUM_THREAD; i++) {
        pthread_create(&tid[i], &attr, runner, argv[1]);
    }
    for (int i=0; i<NUM_THREAD; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("sum = %d \n", sum);
    sleep(1);
}

void * runner(void * param) {
    int upper = atoi(param);

    for (int i=1; i<=upper; i++) {
        sum += i;
    }
    printf("스레드 실행 중~ \n");
    pthread_exit(0);
}