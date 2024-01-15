#ifndef __PARSER_H__
#define __PARSER_H__

typedef struct arguments{
    int argc;
    char ** argv;
} args_t;

args_t * init_args();
args_t * parse(char * str, char * separator);
void print_args(args_t * arguments);
void free_args(args_t * arguments);

#endif
