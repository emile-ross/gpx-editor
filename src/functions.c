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

void wait(long quarters, long seconds)
{
	if (quarters > 0 && quarters < 4)	/* 4 quarters per second */
	{
		quarters *= 250000000;	/* convert quarters to nanoseconds */
	}
	else
	{
		quarters = 0;
		seconds += 1;	/* adds 1 second if 4 >= quarters */
	}

	struct timespec install_timer;
	/* write to timespec struct */
	install_timer.tv_nsec = quarters;
    	install_timer.tv_sec = seconds;
    	nanosleep(&install_timer, NULL);
}
