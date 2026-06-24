#define _POSIX_C_SOURCE 199309L

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "enums.h"

#define max_time_len 32

typedef struct maptime
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} MapTime;

/* global variables */
	extern const char *program_name;
	extern const bool verbose;
	extern const bool ignore_errors;

void clear(void);
void err(const char *error_message);
int command_parsing(int num_args, char *arguments[]);
long time_parsing(int *flag_r_index, int num_args, char *argument[]);
int conversion_check(const char *endptr, const char *input_string, const bool newline);

void stotime(int total_seconds, int *hours, int *minutes, int *seconds);

struct maptime* date_input(void);
int get_time(int lower_bound, int upper_bound, char *date_type);

void wait(long quarters, long seconds);	/* waits for a certain time */

void display_time(struct tm *date);
