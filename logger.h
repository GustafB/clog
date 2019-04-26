#include <stdlib.h>
#include <stdio.h>

typedef enum log_levels { TRACE, INFO, DEBUG, WARN, ERROR, FATAL } log_l;

void log_set_file(FILE *file);

void log_write_log(int level, char *filename, const char *fn_name, int linum, const char* data, ...);
void log_disable_save();
void log_enable_save();
void log_disable_print();
void log_enable_print();
void log_set_level(int level);
void log_initialize_logger(int level);

#define LOG_TRACE(...) log_write_log(0, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_write_log(1, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_write_log(2, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) log_write_log(3, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_write_log(4, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_write_log(5, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
