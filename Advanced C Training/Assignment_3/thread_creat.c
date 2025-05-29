// Online C compiler to run C program online
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int sum = 0;
int N;

int isPrime(int n) {
    if (n <= 1) return 1;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void* threadA(void *arg) {
    for (int i = 1; i < N; i++) {
        if (isPrime(i)) {
            sum += i;
        }
    }
    return NULL;
}

void* threadB(void *arg) {
    for (int i = 0; i < 20; i++) {
        printf("Thread B: Thread 1 is running\n");
        sleep(2);
    }
    return NULL;
}

void* threadC(void *arg) {
    for (int i = 0; i < 20; i++) {
        printf("Thread C: Thread 1 is running\n");
        sleep(3);
    }
    return NULL;
}

int main() {
    printf("Enter a num: ");
    scanf("%d", &N);

    pthread_t tA, tB, tC;

    pthread_create(&tA, NULL, threadA, NULL);
    pthread_create(&tB, NULL, threadB, NULL);
    pthread_create(&tC, NULL, threadC, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    printf("Sum of primes less than %d is %d\n", N, sum);
    printf("Completed\n");
    return 0;
}