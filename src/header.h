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

void stotime(unsigned long total_seconds, uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

uint16_t get_time(uint16_t lower_bound, uint16_t upper_bound, char *date_type, bool eight_bit_conversion);

void wait(long quarters, long seconds);	/* waits for a certain time */

size_t timetotext(char *target, struct maptime *date);
struct maptime current_time(void);
struct maptime date_input(void);

void forwards_write(struct maptime *track_time, int num_waypoints, const unsigned long time_interval);
