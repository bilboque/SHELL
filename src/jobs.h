#ifndef __JOBS_H__
#define __JOBS_H__
#include <sys/types.h>

int exec_job(int argc, char ** argv, pid_t * bg_job, pid_t * fg_job);

#endif
