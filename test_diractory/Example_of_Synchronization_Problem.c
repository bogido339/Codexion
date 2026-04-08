#include <pthread.h>
#include <stdio.h>

pthread_t tid[2];
int counter;

void* trythis(void* arg) {
    counter += 1;
    printf("Job %d started\n", counter);
    for (unsigned long i = 0; i < 0xFFFFFFFF; i++);
    printf("Job %d finished\n", counter);
    return NULL;
}

int main() {
    for (int i = 0; i < 2; i++)
        pthread_create(&tid[i], NULL, trythis, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}