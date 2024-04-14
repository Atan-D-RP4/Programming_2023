#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void *printMessage(void *arg) {
    char *message = (char *)arg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";

    // Create threads
    pthread_create(&thread1, NULL, printMessage, (void *)message1);
    pthread_create(&thread2, NULL, printMessage, (void *)message2);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
