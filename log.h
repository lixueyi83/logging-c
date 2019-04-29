/**
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

#define LOG_VERSION "1.0.0"

enum { TASK_1, TASK_2, TASK_3, TASK_4, TASK_5 };
enum { TERMINAL_NOT_QUIET, TERMINAL_QUIET };
enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };
void logger_config(int task, int level, int quiet, FILE* fp);

#define log_trace(task, ...) log_log(task, LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(task, ...) log_log(task, LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(task, ...)  log_log(task, LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(task, ...)  log_log(task, LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(task, ...) log_log(task, LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(task, ...) log_log(task, LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_log(int task, int level, const char *file, int line, const char *fmt, ...);

#endif
