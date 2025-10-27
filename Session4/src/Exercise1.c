#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
 * Action function : Thread routine that prints thread-specific information.
 * Input param     : arg - pointer to a string message passed when creating the thread.
 * Output param    : None (returns NULL implicitly).
 * Description     :
 *     - Each thread executes this function when created.
 *     - The function prints the message passed from the main thread (arg).
 *     - It also displays the thread's unique ID using pthread_self().
 *     - After sleeping for 1 second to simulate work, the thread prints a termination message.
 */
void* printInfoThread(void *arg)
{
    pthread_t thread_id = pthread_self(); // Get current thread ID

    // Print the message passed as argument
    printf("%s\n", (char *)arg);

    // Display the thread ID
    printf("pthread_t = %lu\n", (unsigned long)thread_id);

    // Simulate thread work (sleep for 1 second)
    sleep(1);

    // Print completion message
    printf("Thread with ID %lu is finished.\n", (unsigned long)thread_id);

    return NULL;
}

/*
 * Action function : Main function that demonstrates basic multithreading using POSIX threads.
 * Input param     : None (standard C main entry point).
 * Output param    : Integer value (0 indicates successful execution).
 * Description     :
 *     - Creates two threads using pthread_create(), each executing printInfoThread().
 *     - Checks for errors during thread creation and prints appropriate messages.
 *     - Waits for both threads to complete using pthread_join().
 *     - After both threads finish, prints a message indicating that the main thread is done.
 */
int main()
{
    // Declare two thread identifiers
    pthread_t threadT1;
    pthread_t threadT2;

    // Create first thread
    int ret1 = pthread_create(&threadT1, NULL, printInfoThread, (void*)"Thread1 is running");
    if (ret1)
    {
        fprintf(stderr, "Error when creating thread1: %d\n", ret1);
        return 1;
    }

    // Create second thread
    int ret2 = pthread_create(&threadT2, NULL, printInfoThread, (void*)"Thread2 is running");
    if (ret2)
    {
        fprintf(stderr, "Error when creating thread2: %d\n", ret2);
        return 1;
    }

    // Wait for both threads to finish
    pthread_join(threadT1, NULL);
    pthread_join(threadT2, NULL);

    // Print completion message from main thread
    printf("Main thread has finished execution.\n");

    return 0;
}