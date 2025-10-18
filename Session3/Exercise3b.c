// Process Orphan:

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
        usleep(5);
        printf("parent process is finish\n ");
    }
    else
    {
        //child process
        int i = 0;
        while(i < 10 ){
        printf("Child process PID (%d), Parent process PID: (%d) \n",getpid(),getppid());
        usleep(1);
        i++;
        }
    }

}