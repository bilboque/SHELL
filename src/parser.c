#include "parser.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HANDLE_PARSER_ERROR(str) {fprintf(stderr, "parser : %s\n", str);return NULL;}

void free_args(args_t * freeme){
    free(freeme->argv);
    free(freeme);
}

void print_args(args_t * arguments){
    for (int i = 0; i < arguments->argc; i++)
        printf("argv[%d] = %s\n", i, arguments->argv[i]);
}

args_t * init_args() {
    args_t * new_args = (args_t *) malloc(sizeof(args_t));

    new_args->argc = 0;
    new_args->argv = (char **) malloc(sizeof(char *));

    return new_args;
}

args_t * parse(char * str, char * sep) {
    args_t * arguments = init_args();

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
