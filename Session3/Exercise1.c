#include <stdlib.h>
#include <unistd.h>     // Need call getpid(), getppid(), fork()
#include <sys/types.h>  // Need call pid_t
#include <sys/wait.h>   // Need call wait()
#include <stdio.h>


int main(){
    pid_t pid;
    int status;

    // Create child process
    pid = fork();

    //Check pid

    if(pid <0){
        perror("fork() faild");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0){
        printf("[Child] This is child process(PID :%d). \n",getpid());
        printf("[Child] I will exit wwith statuc code 5 \n");
        exit(5);
    }
    else
    {
        printf("[Parent] This PID :%d \n",getpid());
        printf("[Parent] This is parent process(PID :%d) \n",getppid());
        printf("[Parent] This is chill process(PID :%d) \n",pid);
        //Wait child process until child process is finish
        wait(&status);
        if(WIFEXITED(status)){
            int exit_status = WEXITSTATUS(status);
            printf("[Parent] Child process terminated with exit code: %d\n", exit_status);
        }else{
            printf("[Parent] The child process terminated abnormally \n");
        }

        
    }
}