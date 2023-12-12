#ifndef __PARSER_H__
#define __PARSER_H__

typedef struct arguments{
    int argc;
    char ** argv;
} args;

args * init_args();
args * parse(char * str, char * separator);
void print_args(args * arguments);
void free_args(args * arguments);

#endif
