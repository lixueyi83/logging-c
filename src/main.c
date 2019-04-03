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
    if(fp == NULL)  printf("file open failed\n");

    /* The only one function used for log setting config */
    log_setting_config(LOG_TRACE, LOG_ENABLE, fp);

    /* log examples */
    log_trace("hello %s", "world");
    log_debug("hello %s", "world");
    log_info("hello %s", "world");
    log_warn("hello %s", "world");
    log_error("hello %s", "world");
    log_fatal("hello %s", "world");

    return 0;
}
