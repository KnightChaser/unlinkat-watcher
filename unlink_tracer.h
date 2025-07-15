// unlink_tracer.h
#ifndef __UNLINK_TRACER_H
#define __UNLINK_TRACER_H

#define MAX_PATH_LEN 384
#define MAX_FILENAME_LEN 128
#define MAX_PROCESS_NAME_LEN 32

/* Ring buffer event for unlink operations */
struct event {
    unsigned int pid;
    char process_name[MAX_PROCESS_NAME_LEN];
    char dir_path[MAX_PATH_LEN];
    char filename[MAX_FILENAME_LEN];
};

#endif // __UNLINK_TRACER_H
