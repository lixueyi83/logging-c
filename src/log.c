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
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "log.h"

/* log config (level,color) pair, different level corresponds to different color 
 * Compiled with -DLOG_USE_COLOR, ANSI color codes will be used when printing.*/
typedef struct{
    int level;
    char* level_str;
    char* color_str;
}LOG_CONFIG;
static const LOG_CONFIG log_config[] = {
    {LOG_TRACE, "TRACE", "\x1b[94m"},
    {LOG_DEBUG, "DEBUG", "\x1b[36m"},
    {LOG_INFO,  "INFO",  "\x1b[32m"},
    {LOG_WARN,  "WARN",  "\x1b[33m"},
    {LOG_ERROR, "ERROR", "\x1b[31m"},
    {LOG_FATAL, "FATAL", "\x1b[35m"}
};

/* log structure and its static instance L */
typedef struct {
    int level;
    int quiet;
    FILE *fp;
}LOG_STRUCT;
static LOG_STRUCT L = { 0, 0, NULL};

/* log_mutex to protect L */
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

/* This is the only log setting config function that should be called if we want
 * to log to a file. 'level' determins which level and above we want to output,
 * 'enable' decides whether we want the terminal logs to be quiet or not, 'fp'
 * is the file descriptor points to the file where we want the log goes to.
 * */
void log_setting_config(int level, int enable, FILE* fp)
{
    L.fp = fp;
    L.level = level;
    L.quiet = enable ? 1 : 0;
}

/* Actuall log function implementation and it's supposed to be thread-safe */
void log_log(int level, const char *file, int line, const char *fmt, ...) 
{
    if(level < L.level) {
        return;
    }

    pthread_mutex_lock(&log_mutex);
    
    time_t t = time(NULL);                  /* Get current time */
    struct tm *lt = localtime(&t);
 
    if(!L.quiet) {                          /* Log to stderr */
        va_list args;
        char buf[16];
        buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
    #ifdef LOG_USE_COLOR
        fprintf(stderr, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
            buf, log_config[level].color_str, log_config[level].level_str, file, line);
    #else
        fprintf(stderr, "%s %-5s %s:%d: ", buf, log_config[level].level_str, file, line);
    #endif
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
        fflush(stderr);
    }
 
    if(L.fp) {                              /* Log to file */
        va_list args;
        char buf[32];
        buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
        fprintf(L.fp, "%s %-5s %s:%d: ", buf, log_config[level].level_str, file, line);
        va_start(args, fmt);
        vfprintf(L.fp, fmt, args);
        va_end(args);
        fprintf(L.fp, "\n");
        fflush(L.fp);
    }

    pthread_mutex_unlock(&log_mutex);
}
