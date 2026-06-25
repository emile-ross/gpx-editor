#include "header.h"

const bool error_checking = true;
const size_t max_line_length = 128;

void forwards_write(struct maptime *track_time, int num_waypoints, const unsigned long time_interval)
{
	/*
	 * members of the struct:
	track_time->year;
	track_time->month;
	track_time->day;
	track_time->hour;
	track_time->second;
	*/

	/* TODO account for division by zero */
	const char *track_time_template = "<when>%u-%u-%uT%02u:%02u:%02uZ</when>";

	char *current_entry = malloc(max_line_length);

	for (int i = 0; i < num_waypoints; i++)
	{
		unsigned long remaining_time = time_interval;
		
		/* add seconds */
		track_time->second += remaining_time % 60;
		remaining_time -= remaining_time % 60;
		
		if (track_time->second >= 60)
		{
			track_time->minute += track_time->second / 60;
			track_time->second %= 60;
		}
		
		/* set minutes */
		unsigned long mins_to_add = (remaining_time / 60) % 60;
		track_time->minute += mins_to_add;
		remaining_time -= mins_to_add * 60;
		
		if (track_time->minute >= 60)
		{
			track_time->hour += track_time->minute / 60;
			track_time->minute %= 60;
		}
		
		/* set hours */
		unsigned long hours_to_add = (remaining_time / (60 * 60)) % 24;
		track_time->hour += hours_to_add;
		remaining_time -= hours_to_add * (60 * 60);
		
		if (track_time->hour >= 24)
		{
			track_time->day += track_time->hour / 24;
			track_time->hour %= 24;
		}
		
		/* write to current_entry buffer */
		snprintf(current_entry, max_line_length, track_time_template, 
				track_time->year,
				track_time->month,
				track_time->day,
				track_time->hour,
				track_time->minute,
				track_time->second);
		printf("%s\n", current_entry);
	}
	free(current_entry);
}
