#ifndef __BUILTIN_H__
#define __BUILTIN_H__

#define EXIT "exit"
#define CD "cd"

#define BUILTIN_CD 0
#define BUILTIN_EXIT 1
#define NOT_BUILTIN 2

#define VALID_BUILTIN {CD, EXIT}
#define N_BUILTIN 2

#define BUILTIN_WRONG_USE(cmd, err) {fprintf(stderr, "%s : %s\n", cmd, err);}
// blalalalalalla
int check_builtin(char * cmd);
int builtin_cd(char * path);
void builtin_exit();

#endif
