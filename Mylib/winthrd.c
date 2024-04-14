#include <stdio.h>
#include <windows.h>

// Function to be executed by each thread
DWORD WINAPI printMessage(LPVOID arg) {
    char *message = (char *)arg;
    printf("%s\n", message);
    return 0;
}

int main() {
    HANDLE thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";

    // Create threads
    thread1 = CreateThread(NULL, 0, printMessage, (LPVOID)message1, 0, NULL);
    thread2 = CreateThread(NULL, 0, printMessage, (LPVOID)message2, 0, NULL);

    // Wait for threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Close thread handles
    CloseHandle(thread1);
    CloseHandle(thread2);

    return 0;
}
