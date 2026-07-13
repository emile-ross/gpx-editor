#include "header.h"

Bool in_bounds(int input)
{
	if (input > 65535 || input < 0)
	{
		err("Out of bounds input");
		return False;
	}
	return True;
}

void time_initialisation(struct maptime* initial_time);

struct maptime current_time(void)
{
	time_t default_time = time(NULL);
	struct tm *cur_time = localtime(&default_time);
	struct maptime current_time_m;
	time_initialisation(&current_time_m);
	
	/* get current year + 1900 because tm struct stores the year from 1900 */
	int y = cur_time->tm_year;
	if (in_bounds(y))
		current_time_m.year = (uint16_t)(1900 + y);

	/* set all other times from tm struct */
	current_time_m.month = 1 + (uint8_t)cur_time->tm_mon;
	current_time_m.day = (uint8_t)cur_time->tm_mday;
	current_time_m.hour = (uint8_t)cur_time->tm_hour;
	current_time_m.minute = (uint8_t)cur_time->tm_min;
	current_time_m.second = (uint8_t)cur_time->tm_sec;

	return current_time_m;
}

void time_initialisation(struct maptime* initial_time)
{
	initial_time->month = 255;
	initial_time->day = 255;
	initial_time->hour = 255;
	initial_time->minute = 255;
	initial_time->second = 255;
}
