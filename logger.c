#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include "logger.h"

static const char *log_level[] = {
    "TRACE", "INFO", "DEBUG", "WARN", "ERROR", "FATAL"
};

static const char *log_colors[] = {
  "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};

static struct {
    char *data;
    FILE *file;
    log_l level;
    int save_log;
    int print_log;
} log_t;


static void
set_time(char *time_buffer)
{
    const time_t raw_time = time(NULL);
    struct tm* local_time = localtime(&raw_time);
    strftime(time_buffer, 32, "%T", local_time);
}

void
log_set_file(FILE *file)
{
    log_t.file = file;
}

void
log_enable_save()
{
    log_t.save_log = 1;
}

void
log_disable_save()
{
    log_t.save_log = 0;
}

void
log_enable_print()
{
    log_t.print_log = 1;
}

void
log_disable_print()
{
    log_t.print_log = 0;
}

void
log_set_level(int level)
{
    log_t.level = level;
}

void
log_initialize_logger()
{
    log_t.data = NULL;
    log_t.file = NULL;
    log_t.level = TRACE;
    log_enable_print();
    log_disable_save();

}

void
log_write_log(int level, char *filename, const char *fn_name, int linum, const char* data, ...)
{
    if (level < (int)log_t.level)
        return;

    char time_buffer[32];
    va_list args;

	set_time(time_buffer);

    if (log_t.print_log == 1)
    {
        fprintf(stderr,
				#ifndef NOCOLOR
                "%s %s%-5s\033[0m %s:%s:%d: ",
				#else
				"%s %s%-5s %s:%s:%d: ",
				#endif
                time_buffer,
                log_colors[level],
                log_level[level],
                filename,
                fn_name,
                linum);

        va_start(args, data);
        vfprintf(stderr, data, args);
        fprintf(stderr, "\n");
        va_end(args);

        fflush(stderr);
    }

    if (log_t.save_log == 1 && log_t.file)
    {
        fprintf(log_t.file,
                "%s %-5s %s:%s:%d: ",
                time_buffer,
                log_level[level],
                filename,
                fn_name,
                linum);

        va_start(args, data);
        vfprintf(log_t.file, data, args);
        fprintf(log_t.file, "\n");
        va_end(args);

        fflush(log_t.file);
    }

}
