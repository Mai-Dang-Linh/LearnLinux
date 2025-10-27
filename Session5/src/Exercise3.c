#include <stdio.h>
#include <unistd.h>
#include <signal.h> // library signal
#include <sys/wait.h> // library waitpid

/*
 * Global variable declaration
 * Type: volatile sig_atomic_t
 * Purpose:
 *     - Used as a flag to safely count the number of received signals.
 *     - 'volatile sig_atomic_t' ensures the variable is accessed atomically
 *       between the main process flow and the signal handler.
 */
volatile sig_atomic_t checkNumberReciverSign = 0;

/*
 * Action function : Signal handler function for the child process.
 * Input param     : sig - integer representing the signal number (SIGUSR1 in this case).
 * Output param    : None.
 * Description     :
 *     - Called automatically whenever the child process receives SIGUSR1.
 *     - Prints a message to indicate a signal was received.
 *     - Increments the global counter 'checkNumberReciverSign'.
 */
void dummy_process_signal(int sig)
{
    printf("Received signal from parent \n");
    checkNumberReciverSign++;
}

/*
 * Action function : Main function that demonstrates parent-child communication via signals.
 * Input param     : None (standard main entry point).
 * Output param    : Integer return value (0 for success).
 * Description     :
 *     - The program creates a child process using fork().
 *     - The child process installs a signal handler for SIGUSR1 using sigaction().
 *     - The parent process sends 5 SIGUSR1 signals to the child.
 *     - The child counts the number of received signals and exits after receiving 5.
 *     - The parent waits for the child process to finish before terminating.
 */

int main()
{
    pid_t pid;  // Variable to store the child process ID

    // Create a new process
    pid = fork();

    if (pid < 0)
    {
        // fork() returns a negative value if process creation fails
        perror("Error creating process\n");
    }
    else if (pid == 0)
    {
        // -------- CHILD PROCESS --------
        struct sigaction sa = {0};  // sigaction structure initialization

        sa.sa_handler = dummy_process_signal; // Assign handler function
        sigemptyset(&sa.sa_mask);             // Clear signal mask
        sa.sa_flags = SA_RESTART;             // Automatically restart interrupted syscalls

        printf("[Child process] - this is pid [%d]\n", getpid());

        // Install signal handler for SIGUSR1
        if (sigaction(SIGUSR1, &sa, NULL))
        {
            perror("sigaction");
            _exit(1);
        }

        // Wait until 5 signals have been received
        while (checkNumberReciverSign < 5)
            pause();  // Sleep until next signal arrives

        _exit(0);  // Exit child process successfully
    }
    else
    {
        // -------- PARENT PROCESS --------
        printf("[Parent process]\n");
        printf("Child process PID: [%d]\n", pid);

        sleep(1); // Wait briefly to ensure child sets up its signal handler

        // Send SIGUSR1 signal to child process 5 times
        for (int i = 0; i < 5; ++i)
        {
            if (kill(pid, SIGUSR1) == -1)
            {
                perror("Kill");
                break;
            }
            sleep(2); // Pause between signals
        }

        // Wait for the child process to complete
        waitpid(pid, NULL, 0);
    }

    return 0;

}