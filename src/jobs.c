#include "jobs.h"
#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <threads.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int exec_fg_job(char ** argv, pid_t * foreground_job){
    int wstatus = 0;
    pid_t cpid = 0;
    pid_t pid = fork();
    if(pid == 0){
        execvp(argv[0], argv);
        fprintf(stderr, "trash: %s - command not found.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0){
        *foreground_job = pid;
        cpid = wait(&wstatus);
        if(cpid == -1){
            perror("wait");
            return -1;
        }
        else{
            printf("FG job %s (PID : %d) exited with code %d\n", argv[0], cpid, wstatus);
            *foreground_job = 0;
            return 0;
        }
    }
    else{
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

int exec_bg_job(int argc, char ** argv){
    argv[argc - 1] = NULL;
    pid_t pid = fork();
    if(pid == 0){
        int fd = open("/dev/null", O_RDONLY);
        if(fd == -1){
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);

        execvp(argv[0], argv);
        fprintf(stderr, "trash: %s - command not found.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0){
        return pid;
    }
    else{
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

int exec_job(int argc, char ** argv, pid_t * bg_job, pid_t * fg_job){
    // printf("last: %s\n", argv[argc - 1]);
    if(strcmp(argv[argc - 1], "&") == 0){
        if(*bg_job > 1){
            printf("Can't execute more than 1 bg job at once\n");
            return -1;
        }
        else{
            return exec_bg_job(argc,argv);
        }
    }
    else{
        return exec_fg_job(argv, fg_job);
    }
}


