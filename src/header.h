#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "enums.h"

/* global variables */
	extern const char *program_name;
	const bool verbose;

void err(const char *error_message);
int command_parsing(int num_args, char *arguments[]);
int time_parsing(int *flag_r_index, int num_args, char *argument[]);
