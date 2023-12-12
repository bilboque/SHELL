#include "parser.h"
#include "jobs.h"
#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#define HANDLE_ERROR(str) {perror(str);}
#define HANDLE_UNEXPECTED_EVENT() {exit(EXIT_FAILURE);}
#define BUFF_SIZE 256

void print_ps() {
    char username[BUFF_SIZE];
    char cwd[1024];

    if (getlogin_r(username, BUFF_SIZE) != 0) {
        perror("getlogin_r");
        exit(EXIT_FAILURE);
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    printf("\033[1;96m┌%s@trash - \033[1;97m%s\n", username, cwd);
    printf("\033[1;96m└$\033[0m");
}

int main(){
    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete);
    // Enable history
    using_history();
    
    char buff[BUFF_SIZE];
    while(1){
        memset(buff, '\0', BUFF_SIZE);
        print_ps();
        char* input = readline(" ");
        strncpy(buff, input, BUFF_SIZE);

        // Check for EOF.
        if (!input){
            break;
        }
        else{
            args * arguments = parse(buff, " ");
            if(arguments == NULL){
                HANDLE_UNEXPECTED_EVENT();
            }

            switch (check_builtin(arguments->argv[0])) {
                case BUILTIN_CD:
                    builtin_cd(arguments->argv[1]);
                    break;
                case BUILTIN_EXIT:
                    builtin_exit();
                    break;
                default:
                    exec_job(arguments->argv);
                    break;
            }

            free_args(arguments);
            free(input);
        }
    }
}
