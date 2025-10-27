#include <stdio.h>
#include <sys/wait.h> //
#include <signal.h> // signal
#include <unistd.h>
#include <poll.h>

//SIGINT - value :2
//SIGTERM - value: 15
/*
 * Action function : Signal handler function that processes incoming signals.
 * Input param     : value - integer signal number (e.g., SIGINT = 2, SIGTERM = 15).
 * Output param    : None (prints messages and may terminate the program).
 * Description     : 
 *     - When SIGINT (Ctrl + C) is received, it prints a message to notify the user.
 *     - When SIGTERM (kill -15 <pid>) is received, it prints a message 
 *       and exits the program safely.
 */
void dummy_process_signal(int value)
{

    if(value == 2)
    {
        printf("\t SIGINT received \n");
    }
    else if(value == 15)
    {
        printf("\t Call SIGTERM. Exiting \n");
        _exit(0);
    }

}

/*
 * Action function : Main function of the program.
 * Input param     : None (standard program entry point).
 * Output param    : Integer status code (0 on normal termination).
 * Description     :
 *     - Registers signal handlers for SIGINT and SIGTERM.
 *     - Uses poll() to wait for keyboard input without blocking signal handling.
 *     - When user types text and presses Enter, it displays the entered data.
 *     - When SIGINT is received, prints "SIGINT received".
 *     - When SIGTERM is received, prints message and exits.
 */
int main()
{
    struct pollfd fds[1];
    int ret = -1;
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    signal(SIGINT,dummy_process_signal); 
    signal(SIGTERM,dummy_process_signal);

    
    
    while(1){
         printf("Enter anything (Ctrl+C = SIGINT, SIGTERM to exit):\n");
        fflush(stdout);
        int ret = poll(fds, 1, -1);
        if(ret == -1)
        {
            perror("poll() error!");
        }
        else if(ret == 0){
            printf("\nTImeout");
        }
        else if(fds[0].revents & POLLIN)
        {
            printf("\nThe your data : \n");
            char buf[128];
            if (fgets(buf, sizeof(buf), stdin)) {
                printf("You entered: %s", buf);
            }
        }
    }


    // while(1)
    // {
    //     pause();
    // }

    return 0;

}