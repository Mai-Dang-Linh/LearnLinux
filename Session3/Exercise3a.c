// Process Zombie:

#include <stdlib.h>
#include <unistd.h>     // Need call getpid(), getppid(), fork()
#include <sys/types.h>  // Need call pid_t
#include <sys/wait.h>   // Need call wait()
#include <stdio.h>

int main()
{
    printf("Excute zombie process \n");
    pid_t pid;
    pid = fork();

    if(pid < 0){
       perror("fork() faild");
       exit(EXIT_FAILURE);
    }
    else if(pid > 0){

        // Parent process
        printf("PID of parent process: (%d),PID of child process: (%d) \n",getppid(),pid);
        while(1){
            usleep(100);
        }
    }
    else
    {
        //Child process
        printf("Child process PID (%d) is dead \n",getpid());
        exit(0);

    }

}