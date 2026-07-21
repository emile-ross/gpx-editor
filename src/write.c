#include "header.h"

const Bool error_checking = True;

int forwards_write(struct maptime *track_time, uint32_t num_waypoints, const uint32_t time_interval)
{
	const char *track_time_template = "<when>%u-%u-%uT%02u:%02u:%02uZ</when>";
	const size_t max_line_length = 128;	/* max length in valid characters (from <when> to </when>) */
	const size_t line_size = max_line_length + 1;	/* account for NULL terminator */

	char (*time_table)[line_size] = malloc(line_size*num_waypoints);

	for (uint32_t i = 0; i < num_waypoints; i++)
	{
		unsigned long remaining_time = time_interval;
		
		/* add seconds */
		track_time->second += (uint8_t)(remaining_time % 60);
		remaining_time -= remaining_time % 60;
		
		if (track_time->second >= 60)
		{
			track_time->minute += track_time->second / 60;
			track_time->second %= 60;
		}
		
		/* set minutes */
		unsigned long mins_to_add = (remaining_time / 60) % 60;
		track_time->minute += (uint8_t)mins_to_add;
		remaining_time -= mins_to_add * 60;
		
		if (track_time->minute >= 60)
		{
			track_time->hour += track_time->minute / 60;
			track_time->minute %= 60;
		}
		
		/* set hours */
		unsigned long hours_to_add = (remaining_time / (60 * 60)) % 24;
		track_time->hour += (uint8_t)hours_to_add;
		remaining_time -= hours_to_add * (60 * 60);
		
		if (track_time->hour >= 24)
		{
			track_time->day += track_time->hour / 24;
			track_time->hour %= 24;
		}
		
		/* write to current_entry buffer */
		snprintf(time_table[i], max_line_length, track_time_template, 
				track_time->year,
				track_time->month,
				track_time->day,
				track_time->hour,
				track_time->minute,
				track_time->second);
	}

	for (uint32_t i = 0; i < num_waypoints; i++)
	{
		printf("%s\n", time_table[i]);
	}

	free(time_table);

	return 0;
}
