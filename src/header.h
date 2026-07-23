#define _POSIX_C_SOURCE 199309L

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "enums.h"
#include "structs.h"

#define UINT8MAX (255)
#define UINT16MAX (65535)
#define INT32MAX (2147483647)
#define UINT32MAX (4294967295)

#define max_num_args (255)

/* global variables */
	extern const char *program_name;
	extern const Bool verbose;
	extern const Bool ignore_errors;

void err(const char *restrict format, ...);
void warn(const char *restrict format, ...);

Bool conversion_check(const char *endptr, const char *input_string, const Bool newline);
int command_parsing(uint8_t *num_args, char *arguments[]);

int32_t time_parsing(uint8_t *flag_r_index, const uint8_t num_args, char *argument[]);
uint16_t get_time(uint16_t lower_bound, uint16_t upper_bound, char *date_type, Bool eight_bit_conversion);
Bool bound_check(int64_t val, int64_t lb, int64_t ub);

/* functions.c */
	void assrt(int expr);
	void clear(void);
	void stotime(long total_seconds, int8_t *hours, int8_t *minutes, int8_t *seconds);
	void wait(long quarters, long seconds);	/* waits for a certain time */
	Bool sufficient_args(struct write_cmd_args command_data);


size_t timetotext(char *target, struct maptime *date);
int forwards_write(struct maptime *track_time, const struct write_arguments *timeargs);

