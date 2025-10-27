#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*
 * Global variable declaration
 * Type: volatile sig_atomic_t
 * Purpose:
 *     - Acts as a counter to track how many times the SIGALRM signal was received.
 *     - Declared as volatile sig_atomic_t to ensure atomic access between the main loop and signal handler.
 */
volatile sig_atomic_t flag = 0;

/*
 * Action function : Signal handler function triggered by the SIGALRM signal.
 * Input param     : int (signal number, automatically passed by the signal system).
 * Output param    : None.
 * Description     :
 *     - This function is called every time the system sends SIGALRM to the process.
 *     - It increments the global counter 'flag' and prints the current timer count.
 *     - When the timer count reaches 10, a message is printed to indicate that the timer exceeded 10 seconds.
 *     - The commented line `alarm(1);` shows how to rearm the alarm if continuous 1-second intervals are needed.
 */
static void alarmTimer(int )
{
    flag++;
    printf("Timer<%d>seconds \n",flag);
    if(flag < 10)
    {
        //trigger alarm every second.
        alarm(1);
    }else{
        printf("Timer greater than 10 \n");
    }
    return;
}

/*
 * Action function : Main function that demonstrates the use of alarm() and signal handling.
 * Input param     : None (standard C main entry point).
 * Output param    : Integer value (0 on normal termination).
 * Description     :
 *     - Registers 'alarmTimer' as the handler for SIGALRM.
 *     - Starts a 1-second timer using alarm(1).
 *     - The main loop uses pause() to suspend execution until a signal is received.
 *     - Each second, SIGALRM triggers the handler, which increments 'flag' and prints the elapsed time.
 *     - The loop continues until the counter reaches 10, then the program exits.
 */
int main()
{
    signal(SIGALRM,alarmTimer);
    // Schedule an alarm signal to occur after 1 second
    alarm(1);
    while(flag< 10)
    {
        pause();// Suspend process until a signal is received
    }
    return 0;
    
}