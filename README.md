# log.c
A simple logging library implemented in C99 originall from:
https://github.com/rxi/log.c 

![screenshot](https://cloud.githubusercontent.com/assets/3920290/23831970/a2415e96-0723-11e7-9886-f8f5d2de60fe.png)


## Usage
**[log.c](src/log.c?raw=1)** and **[log.h](src/log.h?raw=1)** should be dropped
into an existing project and compiled along with it. The library provides 6
function-like macros for logging:

```c
log_trace(const char *fmt, ...);
log_debug(const char *fmt, ...);
log_info(const char *fmt, ...);
log_warn(const char *fmt, ...);
log_error(const char *fmt, ...);
log_fatal(const char *fmt, ...);
```

Each function takes a printf format string followed by additional arguments:

```c
log_trace("Hello %s", "world")
```

Resulting in a line with the given format printed to stderr:

```
20:18:26 TRACE src/main.c:11: Hello world
```

## How to configure settings?
#### void log_setting_config(int level, int enable, FILE* fp);
This is the only log setting config function that should be called if we want
to log to a file. 'level' determins which level and above we want to output,
'enable' decides whether we want the terminal logs to be quiet or not, 'fp'
is the file descriptor that points to the file where we want the log goes to.

## Examples 
There is main.c and a Makefile, just simply run make in command line and you
would be able to see the output messages both from terminal and within the
logfile.txt.

## License
This library is free software; you can redistribute it and/or modify it under
the terms of the MIT license. See [LICENSE](LICENSE) for details.
