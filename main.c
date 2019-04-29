/*************************************************************************
    File Name: main.c
	Author: 
	Mail: 
	Created Time: Wed 03 Apr 2019 11:13:41 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "log.h"

int main(void)
{
    FILE* fp = fopen("logfile.txt", "w");
    if(fp == NULL)
        printf("file open failed\n");

    /* examples for TASK_1 */
    logger_config(TASK_1, LOG_TRACE, TERMINAL_NOT_QUIET, fp);
    log_trace(TASK_1, "hello %s", "world");
    log_debug(TASK_1, "hello %s", "world");
    log_info(TASK_1,  "hello %s", "world");
    log_warn(TASK_1,  "hello %s", "world");
    log_error(TASK_1, "hello %s", "world");
    log_fatal(TASK_1, "hello %s", "world");

    printf("\n");

    /* examples for TASK_2 */
    logger_config(TASK_2, LOG_TRACE, TERMINAL_NOT_QUIET, fp);
    log_trace(TASK_2, "hello %s", "world");
    log_debug(TASK_2, "hello %s", "world");
    log_info(TASK_2,  "hello %s", "world");
    log_warn(TASK_2,  "hello %s", "world");
    log_error(TASK_2, "hello %s", "world");
    log_fatal(TASK_2, "hello %s", "world");

    printf("\n");

    /* examples for TASK_3 */
    logger_config(TASK_3, LOG_TRACE, TERMINAL_NOT_QUIET, fp);
    log_trace(TASK_3, "hello %s", "world");
    log_debug(TASK_3, "hello %s", "world");
    log_info(TASK_3,  "hello %s", "world");
    log_warn(TASK_3,  "hello %s", "world");
    log_error(TASK_3, "hello %s", "world");
    log_fatal(TASK_3, "hello %s", "world");

    printf("\n");

    /* examples for TASK_4 */
    logger_config(TASK_4, LOG_TRACE, TERMINAL_NOT_QUIET, fp);
    log_trace(TASK_4, "hello %s", "world");
    log_debug(TASK_4, "hello %s", "world");
    log_info(TASK_4,  "hello %s", "world");
    log_warn(TASK_4,  "hello %s", "world");
    log_error(TASK_4, "hello %s", "world");
    log_fatal(TASK_4, "hello %s", "world");

    printf("\n");

    /* examples for TASK_5 */
    logger_config(TASK_5, LOG_TRACE, TERMINAL_NOT_QUIET, fp);
    log_trace(TASK_5, "hello %s", "world");
    log_debug(TASK_5, "hello %s", "world");
    log_info(TASK_5,  "hello %s", "world");
    log_warn(TASK_5,  "hello %s", "world");
    log_error(TASK_5, "hello %s", "world");
    log_fatal(TASK_5, "hello %s", "world");

    return 0;
}
