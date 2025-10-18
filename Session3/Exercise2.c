//Thay the Ma thuc thi va Tuong tac voi Moi truong

#include <stdlib.h>
#include <unistd.h>     // Need call getpid(), getppid(), fork()
#include <sys/types.h>  // Need call pid_t
#include <sys/wait.h>   // Need call wait()
#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("The input argument is incorrect \n");
        return 1;
    }
    pid_t pid;
    int status;
    const char* code = argv[1];
    if(setenv("MY_COMMAND",code,1) != 0){
        perror("Error setenv");
        return 1;
    }

    pid = fork();

    if(pid < 0){
       perror("fork() faild");
       exit(EXIT_FAILURE);
    }else if(pid >0){
        //parent process
        printf("[Parent] This PID :%d \n",getpid());
        printf("[Parent] This is parent process(PID :%d) \n",getppid());
        printf("[Parent] This is chill process(PID :%d) \n",pid);
        waitpid(pid,&status,0);
        printf("Child process is finished\n");


    }else{
        //child process
        printf("[Child] This is child process(PID :%d). \n",getpid());

        char * command = getenv("MY_COMMAND");
        if(!command){
            fprintf(stderr,"MY_COMMAND is not set \n");
            exit(1);
        }
        printf("[Child] Execute('%s'): \n",command);
        execlp(command,command,NULL);
        perror("execlp");
        printf("\n");
        printf("[Child] This is child process(PID :%d). \n",getpid());
        _exit(1);
    }

    return 0;
}