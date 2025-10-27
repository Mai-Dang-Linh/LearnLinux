#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
 * ===============================================================
 *  Program Name  : Reader-Writer Lock Example using pthread_rwlock
 *  Description   : Demonstrates synchronization of multiple reader
 *                  and writer threads accessing a shared variable.
 *  Author        : [Your Name]
 *  Date          : [Insert Date]
 *  Version       : 1.0
 * ===============================================================
 */

/*
 * Constant definitions
 * NUM_READERS : number of reader threads to create
 * NUM_WRITES  : number of writer threads to create
 */
#define NUM_READERS 5
#define NUM_WRITES  2

/*
 * Global variable declaration
 * Name           : rwlock
 * Type           : pthread_rwlock_t
 * Purpose        :
 *     - Reader–writer lock used to control concurrent access to shared data.
 *     - Allows multiple readers to access data simultaneously,
 *       but only one writer can modify data at a time (exclusive access).
 */
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

/*
 * Global variable declaration
 * Name           : result
 * Type           : int
 * Purpose        :
 *     - Shared resource accessed by both reader and writer threads.
 *     - Writers increment this variable; readers print its value.
 */
int result = 0;

/*
 * Action function : Reader thread routine.
 * Input param     : arg - optional thread ID pointer (unused here).
 * Output param    : None (returns NULL).
 * Description     :
 *     - Continuously reads the shared variable 'result' while holding
 *       a read lock (pthread_rwlock_rdlock).
 *     - Multiple readers can hold the lock concurrently.
 *     - Prints the thread ID and current value of 'result'.
 *     - Releases the read lock after reading.
 *     - Sleeps for 200 milliseconds between reads.
 */
void* readThread(void* arg)
{
    int *id = (int*)arg;

    while (1)
    {
        // Acquire read lock (shared mode)
        pthread_rwlock_rdlock(&rwlock);

        // Print reader thread ID and current data
        printf("[Reader ID: %lu] - Output data: %d\n",
               (unsigned long)pthread_self(), result);

        // Release read lock
        pthread_rwlock_unlock(&rwlock);

        // Sleep for 0.2 seconds before reading again
        usleep(200000);
    }

    return NULL;
}

/*
 * Action function : Writer thread routine.
 * Input param     : arg - optional thread ID pointer (unused here).
 * Output param    : None (returns NULL).
 * Description     :
 *     - Continuously updates the shared variable 'result' by incrementing it.
 *     - Acquires the write lock (pthread_rwlock_wrlock) before modifying data.
 *     - Only one writer can hold the lock at a time; all readers/writers are blocked until released.
 *     - Prints the thread ID and updated value of 'result'.
 *     - Releases the write lock after updating.
 *     - Sleeps for 1 second between writes.
 */
void* writeThread(void* arg)
{
    int *id = (int*)arg;

    while (1)
    {
        // Acquire write lock (exclusive mode)
        pthread_rwlock_wrlock(&rwlock);

        // Modify shared variable
        result += 1;

        // Print writer thread ID and new result value
        printf(">>> [Writer ID: %lu] - Updated result: %d\n",
               (unsigned long)pthread_self(), result);

        // Release write lock
        pthread_rwlock_unlock(&rwlock);

        // Sleep for 1 second before next update
        sleep(1);
    }

    return NULL;
}

/*
 * Action function : Main function — entry point of the program.
 * Input param     : None (standard C main entry point).
 * Output param    : Integer (0 on success).
 * Description     :
 *     - Initializes the reader–writer lock.
 *     - Creates multiple reader and writer threads.
 *     - Each reader continuously reads shared data while writers update it.
 *     - Uses pthread_join() to wait for all threads (infinite loop case).
 *     - Destroys the rwlock before program termination (not reached in this demo).
 */
int main()
{
    // Initialize reader-writer lock
    pthread_rwlock_init(&rwlock, NULL);

    // Declare thread identifiers for readers and writers
    pthread_t readers[NUM_READERS], writers[NUM_WRITES];

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_create(&readers[i], NULL, readThread, NULL);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITES; i++)
    {
        pthread_create(&writers[i], NULL, writeThread, NULL);
    }

    // Wait for reader threads to complete (infinite loop)
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    // Wait for writer threads to complete (infinite loop)
    for (int i = 0; i < NUM_WRITES; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Destroy reader-writer lock (unreachable in this program)
    pthread_rwlock_destroy(&rwlock);

    return 0;
}