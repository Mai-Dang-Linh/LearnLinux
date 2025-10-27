#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

/*
 * Global variable declaration
 * Name           : countSignal
 * Type           : int
 * Purpose        : 
 *     - Counts how many times the program has received the SIGINT signal (Ctrl + C).
 *     - Used to control the main loop and stop execution after receiving the signal twice.
 */
int countSignal = 0;

/*
 * Action function : Signal handler function for SIGINT (Ctrl + C).
 * Input param     : sig - integer signal number automatically passed by the signal system.
 * Output param    : None.
 * Description     :
 *     - Called automatically whenever SIGINT is sent to the program (typically by pressing Ctrl + C).
 *     - Prints the received signal number and its corresponding string name using strsignal().
 *     - Increments the global variable 'countSignal' to keep track of how many times SIGINT was received.
 *     - The commented-out code shows where you could add logic to stop handling signals after a certain count.
 */
void signal_terminal(int sig)
{
    printf("SIGINT received [%d]-[%s] \n",sig,strsignal(sig));
    countSignal++;
    // if(countSignal>2){
    //     return;
    // }
}

/*
 * Action function : Main function that demonstrates signal handling for SIGINT.
 * Input param     : None (standard main entry point).
 * Output param    : Integer return value (0 indicates successful termination).
 * Description     :
 *     - Registers 'signal_terminal' as the handler for SIGINT using the signal() function.
 *     - Continuously prints a status message every 2 seconds while waiting for user signals.
 *     - When the user presses Ctrl + C, SIGINT is sent to the process and handled by 'signal_terminal'.
 *     - After receiving two SIGINT signals, the loop ends and the program terminates gracefully.
 */

int main(){

    // Register signal handler for SIGINT (Ctrl + C)
    signal(SIGINT,signal_terminal);
    printf("Program is running.Press Ctr+C to send SIGINT...\n");

    // Main loop: waits for up to two SIGINT signals before exiting
    while(countSignal<2){
        printf("Waiting for signal...\n");
        sleep(2);// Sleep for 2 seconds before checking again
    }
    countSignal = 0; 
    return 0;

}