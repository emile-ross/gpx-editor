#include "header.h"

struct maptime current_time(void)
{
	time_t default_time = time(NULL);
	struct tm cur_time = localtime(&default_time);

	struct maptime current_time_m;
	
	current_time_m.year = cur_time.year;

	return current_time_m;
}
