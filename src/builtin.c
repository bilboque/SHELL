#include "builtin.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void builtin_exit() {
    exit(EXIT_SUCCESS);
}

int builtin_cd(char * path){
    int ret = 0;
    if(path == NULL || strcmp(path, "~") == 0){
        ret = chdir(getenv("HOME"));
    }
    else{
        ret = chdir(path);
    }
    if(errno != 0){
        perror("cd");
    }
    return ret;
}

int check_builtin(char * cmd){
    char * builtins[] = VALID_BUILTIN;
    for(int i = 0; i<N_BUILTIN; i++){
        if(strcmp(cmd, builtins[i]) == 0){
            return i; // VALID_BUILTIN est construit de manière a ce que ce hack marche
        }
    }
    return NOT_BUILTIN;
}
