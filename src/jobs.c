#include "jobs.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <threads.h>
#include <sys/wait.h>
#include <unistd.h>

int exec_job(char ** argv){
    int wstatus = 0;
    pid_t cpid = 0;
    pid_t pid = fork();

    if(pid == 0){
        execvp(argv[0], argv);
        fprintf(stderr, "trash: %s - command not found.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0){
        cpid = wait(&wstatus);
        if(cpid == -1){
            perror("wait");
            return -1;
        }
        else{
            // printf("FG job %s (PID : %d) exited with code %d\n", argv[0], cpid, wstatus);
            return 0;
        }
    }
    else{
        perror("fork");
        exit(EXIT_FAILURE);
    }
}
