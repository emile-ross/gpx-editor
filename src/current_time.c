#include "header.h"

struct maptime current_time(void)
{
	time_t default_time = time(NULL);
	struct tm cur_time = localtime(&default_time);

	struct maptime current_time_m;
	
	current_time_m.year = cur_time.year;
	current_time_m.month = cur_time.month;
	current_time_m.day = cur_time.mday;
	current_time_m.minute = cur_time.min;
	current_time_m.second = cur_time.sec;

	return current_time_m;
}
