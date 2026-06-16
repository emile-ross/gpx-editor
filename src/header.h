#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

void date_input(void);
long get_time(int lower_bound, int upper_bound, char *date_type);
