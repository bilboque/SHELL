#include "builtin.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void builtin_exit(){
    exit(EXIT_SUCCESS);
}

int builtin_cd(char * path){
    int ret = 0;
    if(path == NULL)
        ret = chdir(getenv("HOME"));
    else if(path[0] == '~'){
        ret = chdir(getenv("HOME"));
        if(path[1] != '\0' && ret == 0)
            ret = chdir(path + 2);
    }
    else
        ret = chdir(path);

    if(ret == -1)
        perror("cd");
    return ret;
}

int check_builtin(char * cmd){
    char * builtins[] = VALID_BUILTIN;
    for(int i = 0; i<N_BUILTIN; i++)
        if(strcmp(cmd, builtins[i]) == 0)
            return i; // VALID_BUILTIN est construit de manière a ce que ce hack marche

    return NOT_BUILTIN;
}
