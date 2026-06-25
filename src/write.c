#include "header.h"

void forwards_write(struct maptime *track_time, int num_waypoints, const unsigned long time_interval)
{
	track_time->year;
	track_time->month;
	track_time->day;
	track_time->hour;
	track_time->second;

	for (int i = 0; i < num_waypoints; i++);
	{
		unsigned long interval = time_interval;

		uint8_t seconds = track_time->second + interval % 60; 

		if (seconds >= 60)
		{
			track_time->minute++;
			seconds -= 60;
		}
		interval -= interval % 60;

		track_time->second = seconds;
	}
	const char *track_time_template = "<when>%u-%u-%uT%u:%u:%uZ</when>";
}
