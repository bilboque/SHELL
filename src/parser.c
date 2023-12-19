#include "parser.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HANDLE_PARSER_ERROR(str) {fprintf(stderr, "parser : %s\n", str);return NULL;}

void free_args(args * freeme){
    free(freeme->argv);
    free(freeme);
}

void print_args(args * arguments){
    for (int i = 0; i < arguments->argc; i++){
        printf("argv[%d] = %s\n", i, arguments->argv[i]);
    }
}

args * init_args() {
    args * new_args = (args *) malloc(sizeof(args));

    new_args->argc = 0;
    new_args->argv = (char **) malloc(sizeof(char *));

    return new_args;
}

args * parse(char * str, char * sep) {
    args * arguments = init_args();

    char * token = strtok(str, sep);
    if (token == NULL) {
        free(arguments);
        return NULL;
    }

    while (token != NULL) {
        arguments->argv[arguments->argc++] = token;
        token = strtok(NULL, sep);
        arguments->argv = reallocarray(arguments->argv, arguments->argc, (sizeof(char *) * (arguments->argc + 1)));
        arguments->argv[arguments->argc] = NULL;
    }

    return arguments;
}
