/******************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#include "log.h"

/* 8 bright colors:
 * Bright Black:   \x1b[30;1m
 * Bright Red:     \x1b[31;1m
 * Bright Green:   \x1b[32;1m
 * Bright Yellow:  \x1b[33;1m
 * Bright Blue:    \x1b[34;1m
 * Bright Magenta: \x1b[35;1m
 * Bright Cyan:    \x1b[36;1m
 * Bright White:   \x1b[37;1m
 * Bright Reset:   \x1b[0m
 * */


struct taskcolor_t {
    int id;
    char* name;
    char* color;
};
static struct taskcolor_t task_list[] = {
    { TASK_1, "TASK_1", "\x1b[30;1m" },
    { TASK_2, "TASK_2", "\x1b[31;1m" },
    { TASK_3, "TASK_3", "\x1b[33;1m" },
    { TASK_4, "TASK_4", "\x1b[34;1m" },
    { TASK_5, "TASK_5", "\x1b[36;1m" } 
};                    

/* log config (level,color) pair, different level corresponds to different color 
 * Compiled with -DLOG_USE_COLOR, ANSI color codes will be used when printing.*/
typedef struct{
    int level;
    char* name;
    char* color;
}logcolor_t;
static const logcolor_t log_config[] = {
    { LOG_TRACE, "TRACE", "\x1b[37m" },
    { LOG_DEBUG, "DEBUG", "\x1b[36m" },
    { LOG_INFO,  "INFO" , "\x1b[35m" },
    { LOG_WARN,  "WARN" , "\x1b[34m" },
    { LOG_ERROR, "ERROR", "\x1b[33m" },
    { LOG_FATAL, "FATAL", "\x1b[31m" }
};

/* log structure and its static instance logger */
typedef struct {
    int task;   /* only enable a specific task log output */
    int level;  /* debug level */
    int quiet;  /* terminal quiet or not */
    FILE *fp;   /* log file */
}LOG_STRUCT;
static LOG_STRUCT logger = { 0, 0, 0, NULL};

/* log_mutex to protect logger */
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

/* The only function used to configure logger settings:
 *  'level': determins which level and above we want to output,
 *  'quiet': decides whether we want the terminal logs to be quiet or not, 
 *  'fp'   : the file descriptor points to the file where we want the log goes to.
 */
void logger_config(int task, int level, int quiet, FILE* fp)
{
    logger.task = task;
    logger.level = level;
    logger.quiet = quiet ? 1 : 0;
    logger.fp = fp;
}

/* Actuall log function implementation and it's supposed to be thread-safe */
void log_log(int task, int level, const char *file, int line, const char *fmt, ...) 
{
    if(logger.task != task)
        return;

    if(level < logger.level)
        return;

    pthread_mutex_lock(&log_mutex);
    
    /* get current timestamp */
    time_t t = time(NULL);
    struct tm *ltime = localtime(&t);
    char timestamp[30];
    timestamp[strftime(timestamp, sizeof(timestamp), "%x %X", ltime)] = '\0';
 
    if(!logger.quiet) {
        va_list args;
        #ifdef LOG_USE_COLOR
        fprintf(stderr, "%s %s %s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ", 
                timestamp, task_list[task].color, task_list[task].name, 
                log_config[level].color, log_config[level].name, file, line);
        #else
        fprintf(stderr, "%s %s %s %s %-5s %s:%d: ", 
                __DATE, timestamp, task_list[task].color,  task_list[task].name, 
                log_config[level].name, file, line);
        #endif
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
        fflush(stderr);
    }
 
    if(logger.fp) {
        va_list args;
        fprintf(logger.fp, "%s %s %-5s %s:%d: ", 
                timestamp, task_list[task].name, log_config[level].name,  file, line);
        va_start(args, fmt);
        vfprintf(logger.fp, fmt, args);
        va_end(args);
        fprintf(logger.fp, "\n");
        fflush(logger.fp);
    }

    pthread_mutex_unlock(&log_mutex);
}
