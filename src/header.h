#define _POSIX_C_SOURCE 199309L

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "enums.h"

#define UINT8MAX (255)
#define UINT16MAX (65535)
#define UINT32MAX (4294967295)

typedef enum 
{
	False = 0,
	True = 1
} Bool;

typedef struct maptime
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} MapTime;

typedef struct
{
	Bool interval_specified;
	Bool start_time_specified;
	Bool end_time_specified;
}  output_arguments_bl;

/* global variables */
	extern const char *program_name;
	extern const Bool verbose;
	extern const Bool ignore_errors;

void err(const char *restrict format, ...);
void warn(const char *restrict format, ...);

void clear(void);
Bool conversion_check(const char *endptr, const char *input_string, const Bool newline);
void wait(long quarters, long seconds);	/* waits for a certain time */
int command_parsing(int num_args, char *arguments[]);

uint32_t time_parsing(int *flag_r_index, int num_args, char *argument[]);
uint16_t get_time(uint16_t lower_bound, uint16_t upper_bound, char *date_type, Bool eight_bit_conversion);
Bool bound_check(int64_t val, int64_t lb, int64_t ub);

void stotime(unsigned long total_seconds, uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

size_t timetotext(char *target, struct maptime *date);
struct maptime current_time(void);
struct maptime date_input(void);

int forwards_write(struct maptime *track_time, uint32_t num_waypoints, const uint32_t time_interval);
