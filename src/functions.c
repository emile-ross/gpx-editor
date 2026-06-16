#include "header.h"

void stotime(int total_seconds, int *hours, int *minutes, int *seconds)
{
	int seconds_remainder = total_seconds % 60;
	*seconds = seconds_remainder;

	int minutes_pre_remainder = total_seconds - seconds_remainder;
	int minutes_remainder = minutes_pre_remainder % 3600;
	*minutes = minutes_remainder / 60;

	int hours_temp = minutes_pre_remainder - minutes_remainder;
	*hours = hours_temp / 3600;
}

void clear(void)
{
	/* This ANSI sequence clears the screen */
	printf("\033[2J\033[H");
}

void wait(int quarters_seconds, int num_seconds)
{
	struct timespec install_timer;
	long int time_timer_quarters;
	long int time_timer_seconds;

	if (quarters_seconds < 4)	/* 4 quarters per second */
	{
		time_timer_quarters = quarters_seconds * 250000000;	/* convert quarters to nanoseconds */
		time_timer_seconds = num_seconds;			/* set seconds */
	}
	else
	{
		time_timer_quarters = 0;
		time_timer_seconds = num_seconds + 1;	/* adds 1 second if 4 >= quarters */
	}

	install_timer.tv_nsec = time_timer_quarters;
    	install_timer.tv_sec = time_timer_seconds;
    	nanosleep(&install_timer, NULL);
}
