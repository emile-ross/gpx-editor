#include "header.h"

bool in_bounds(int input)
{
	if (input > 65535 || input < 0)
	{
		err("Out of bounds input\n");
		return false;
	}
	return true;
}

struct maptime current_time(void)
{
	time_t default_time = time(NULL);
	struct tm *cur_time = localtime(&default_time);

	struct maptime current_time_m;
	
	/* get current year + 1900 because tm struct stores the year from 1900 */
	int y = cur_time->tm_year;
	if (in_bounds(y))
		current_time_m.year = (uint16_t)(1900 + y);

	/* set all other times from tm struct */
	int month = cur_time->tm_mon;
	if (in_bounds(month))
		current_time_m.month = (uint8_t)month;
	int day = cur_time->tm_mday;
	if (in_bounds(day))
		current_time_m.day = (uint8_t)day;
	int mi = cur_time->tm_min;
	if (in_bounds(mi))
		current_time_m.day = (uint8_t)mi;
	int seconds = cur_time->tm_sec;
	if (in_bounds(seconds))
		current_time_m.day = (uint8_t)seconds;

	return current_time_m;
}
