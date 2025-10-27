#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
 * Global variable declaration
 * Name           : counter
 * Type           : long long
 * Purpose        :
 *     - Acts as a shared resource that all threads will increment.
 *     - Used to demonstrate synchronization using mutex locks to prevent race conditions.
 */
long long counter = 0;

/*
 * Global variable declaration
 * Name           : lock
 * Type           : pthread_mutex_t
 * Purpose        :
 *     - Mutex (mutual exclusion) lock used to control access to the shared variable 'counter'.
 *     - Ensures that only one thread updates 'counter' at a time.
 */
pthread_mutex_t lock;

/*
 * Action function : Thread routine that increments the shared counter variable.
 * Input param     : arg - pointer to a string message passed from main() when the thread is created.
 * Output param    : None (returns NULL).
 * Description     :
 *     - Each thread executes this function when created.
 *     - It prints the message received as input (to indicate which thread is running).
 *     - Inside a loop, each thread increments the shared global variable 'counter' one million times.
 *     - A mutex lock is used around the critical section to prevent data races between threads.
 *     - The function returns NULL when completed.
 */
void* printInfoThread(void *arg)
{
    pthread_t thread_id = pthread_self(); // Get current thread ID

    printf("%s\n", (char *)arg); // Print thread message

    for (int i = 0; i <= 1000000; ++i)
    {
        pthread_mutex_lock(&lock);   // Lock critical section
        counter += 1;                // Increment shared counter
        pthread_mutex_unlock(&lock); // Unlock after updating
    }

    return NULL;
}

/*
 * Action function : Main function that demonstrates multi-threaded synchronization using mutex locks.
 * Input param     : None (standard main entry point).
 * Output param    : Integer value (0 for success, 1 for error).
 * Description     :
 *     - Initializes the mutex lock.
 *     - Creates three threads, each executing the printInfoThread() routine.
 *     - Each thread concurrently increments a shared variable 'counter' one million times.
 *     - The mutex ensures that increments are atomic and thread-safe.
 *     - The main thread waits for all threads to complete using pthread_join().
 *     - After all threads finish, the total value of 'counter' is printed to confirm synchronization.
 *     - Finally, the program prints a completion message and exits.
 */
int main()
{
    // Thread identifiers
    pthread_t threadT1;
    pthread_t threadT2;
    pthread_t threadT3;

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create three threads
    int ret1 = pthread_create(&threadT1, NULL, printInfoThread, (void*)"Thread1 is running");
    if (ret1)
    {
        fprintf(stderr, "Error when creating thread1: %d\n", ret1);
        return 1;
    }

    int ret2 = pthread_create(&threadT2, NULL, printInfoThread, (void*)"Thread2 is running");
    if (ret2)
    {
        fprintf(stderr, "Error when creating thread2: %d\n", ret2);
        return 1;
    }

    int ret3 = pthread_create(&threadT3, NULL, printInfoThread, (void*)"Thread3 is running");
    if (ret3)
    {
        fprintf(stderr, "Error when creating thread3: %d\n", ret3);
        return 1;
    }

    // Wait for all threads to complete
    pthread_join(threadT1, NULL);
    pthread_join(threadT2, NULL);
    pthread_join(threadT3, NULL);

    // Print the final result of the shared counter
    printf("Result of count: %lld\n", counter);
    printf("Main thread finished execution.\n");

    // Destroy mutex after all threads are done
    pthread_mutex_destroy(&lock);
}