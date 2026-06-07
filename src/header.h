#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "enums.h"

extern char *program_name;

void err(const char *error_message);
int command_parsing(int num_args, char *arguments[]);

