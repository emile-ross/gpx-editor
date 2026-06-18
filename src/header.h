#define _POSIX_C_SOURCE 199309L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "enums.h"

#define max_time_len 32

/* global variables */
	extern const char *program_name;
	extern const bool verbose;

void clear(void);
void err(const char *error_message);
int command_parsing(int num_args, char *arguments[]);
int time_parsing(int *flag_r_index, int num_args, char *argument[]);

void stotime(int total_seconds, int *hours, int *minutes, int *seconds);

struct tm date_input(void);
int get_time(int lower_bound, int upper_bound, char *date_type);

void wait(int quarters_seconds, int num_seconds);
