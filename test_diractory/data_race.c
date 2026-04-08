#include <pthread.h>
#include <stdio.h>

int counter = 0; // Shared resource

void* increment_counter(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        // DATA RACE HERE:
        // Multiple threads reading and writing 'counter' at the same time
        counter++; 
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads performing the same task
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter value: %d\n", counter);
    printf("Expected value: 2000000\n");

    return 0;
}