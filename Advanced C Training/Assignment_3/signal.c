#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

long long sum = 0; // Use long long for larger sums
int N;
volatile sig_atomic_t keep_running = 1; // Flag to control thread execution

// Signal handler for SIGINT
void signal_handler(int sig) {
    printf("\nSIGINT received. Stopping threads...\n");
    keep_running = 0;
}

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1) return 0; // Fix: 1 is not prime
    for (int i = 2; i * i <= n; i++) { // Optimize: check up to square root
        if (n % i == 0) return 0;
    }
    return 1;
}

// Function for Thread A: Calculate sum of first N prime numbers
void* threadA(void *arg) {
    clock_t start = clock();
    int count = 0, num = 2;
    while (count < N && keep_running) {
        if (isPrime(num)) {
            sum += num;
            count++;
        }
        num++;
    }
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    if (keep_running) {
        printf("Thread A - Sum of first %d prime numbers: %lld\n", N, sum);
    }
    printf("Thread A - Time taken: %.2f seconds\n", time_taken);
    return NULL;
}

// Function for Thread B: Print "Thread 1 is running" every 2 seconds
void* threadB(void *arg) {
    clock_t start = clock();
    for (int i = 0; i < 20 && keep_running; i++) {
        printf("Thread B: Thread 1 is running\n");
        sleep(2);
    }
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Thread B - Time taken: %.2f seconds\n", time_taken);
    return NULL;
}

// Function for Thread C: Print "Thread 2 is running" every 3 seconds
void* threadC(void *arg) {
    clock_t start = clock();
    for (int i = 0; i < 20 && keep_running; i++) {
        printf("Thread C: Thread 2 is running\n"); // Fixed message
        sleep(3);
    }
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Thread C - Time taken: %.2f seconds\n", time_taken);
    return NULL;
}

int main() {
    // Set up signal handling
    signal(SIGINT, signal_handler);

    printf("Enter a num: ");
    scanf("%d", &N);

    pthread_t tA, tB, tC;
    clock_t program_start = clock();

    printf("Main: Starting threads at %s", ctime(&(time_t){time(NULL)}));

    // Create threads
    pthread_create(&tA, NULL, threadA, NULL);
    pthread_create(&tB, NULL, threadB, NULL);
    pthread_create(&tC, NULL, threadC, NULL);

    // Wait for all threads to finish
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    clock_t program_end = clock();
    double total_time = (double)(program_end - program_start) / CLOCKS_PER_SEC;
    printf("Main: All threads completed at %s", ctime(&(time_t){time(NULL)}));
    printf("Main: Total execution time: %.2f seconds\n", total_time);
    printf("Completed\n");
    return 0;
}