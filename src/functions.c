#include "header.h"

void stotime(unsigned long total_seconds, uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
	unsigned long seconds_remainder = total_seconds % 60;
	/* this cast is correct because we have a modulus operator
	 * with 60, guaranteeing a value less than 60 */
	*seconds = (uint8_t)seconds_remainder;	

	unsigned long minutes_pre_remainder = total_seconds - seconds_remainder;
	unsigned long minutes_remainder = minutes_pre_remainder % 3600;
	*minutes = (uint8_t)(minutes_remainder / 60);

	unsigned long hours_temp = minutes_pre_remainder - minutes_remainder;
	*hours = (uint8_t)(hours_temp / 3600);
}

void clear(void)
{
	/* This ANSI sequence clears the screen */
	printf("\033[2J\033[H");
}

void wait(long quarters, long seconds)
{
	if ((quarters > 0) && (quarters < 4))	/* 4 quarters per second */
	{
		quarters *= 250000000;	/* convert quarters to nanoseconds */
	}
	else
	{
		/* adds the number of seconds corresponding to the number of quarters divided by 4 */
		seconds += (long)(quarters / 4);
		quarters = 0;
	}

	struct timespec install_timer;
	/* write to timespec struct */
	install_timer.tv_nsec = quarters;
    	install_timer.tv_sec = seconds;

    	nanosleep(&install_timer, NULL);	/* execute nanosleep function and pass in the timespect struct */
}

bool conversion_check(const char *endptr, const char *input_string, const bool newline)
{
	/* this doesn't need any error messages 
	 * they will be handled by the function callee */
	if (!ignore_errors)
	{
		/* exits if valid */
		if (*endptr == '\0')
		{
			return true;
		}

		if (strcmp(endptr, input_string) == 0)
		{
			/* nothing in the string matches */
			return false;
		}

		if (newline)
		{
			if (*endptr == '\n')
			{
				return true;
			}
		}
		return false;
	}
	return true;
}
