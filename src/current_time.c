#include "header.h"

Bool in_bounds(long input, long upper_bound)
{
	if (input > upper_bound || input < 0)
	{
		err("Out of bounds input");
		return False;
	}
	return True;
}

void assrt(int expr)
{
	if (!expr)
	{
		fprintf(stderr, "Assertion failed (integer is out of bounds)\n");
		exit(1);
	}
}

void time_initialisation(struct maptime* initial_time);

struct maptime current_time(void)
{
	time_t default_time = time(NULL);
	struct tm *cur_time = localtime(&default_time);
	struct maptime current_time_m;
	time_initialisation(&current_time_m);
	
	/* get current year + 1900 because tm struct stores the year from 1900 */
	assrt(UINT16MAX > (cur_time->tm_year + 1900));
	current_time_m.year = (uint16_t)(cur_time->tm_year + 1900);

	/* set all other times from tm struct */
	assrt(UINT8MAX > cur_time->tm_mon);
	current_time_m.month = 1 + (uint8_t)cur_time->tm_mon;
	assrt(UINT8MAX > cur_time->tm_mday);
	current_time_m.day = (uint8_t)cur_time->tm_mday;
	assrt(UINT8MAX > cur_time->tm_hour);
	current_time_m.hour = (uint8_t)cur_time->tm_hour;
	assrt(UINT8MAX > cur_time->tm_min);
	current_time_m.minute = (uint8_t)cur_time->tm_min;
	assrt(UINT8MAX > cur_time->tm_sec);
	current_time_m.second = (uint8_t)cur_time->tm_sec;

	return current_time_m;
}

void time_initialisation(struct maptime* initial_time)
{
	/* this initialises the initial_time struct with the integer max 
	 * in order to make it clear that this struct is empty */
	initial_time->month = UINT8MAX;
	initial_time->day = UINT8MAX;
	initial_time->hour = UINT8MAX;
	initial_time->minute = UINT8MAX;
	initial_time->second = UINT8MAX;
}
