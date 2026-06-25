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
	const char *track_time_template = "<when>%u-%u-%uT%u:%u:%uZ</when>";
	for (int i = 0; i < num_waypoints; i++)
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

		uint8_t minutes = track_time->minute + ((interval % 3600)/60); 

		if (minutes >= 60 && minutes <= 120)
		{
			track_time->hour++;
			minutes -= 60;
		}
		else if (minutes >= 120)
		{
			/* can't be ignored if even if there is no error checking */
			err("Invalid number of minutes");
		}

		interval -= (interval % ((interval % 3600)/60));

		/* set the minute struct member as the minutes local variable */
		track_time->minute = minutes;

		uint8_t hours = (uint8_t)(track_time->hour + (interval / 3600));
		if (hours >= 24)
		{
			hours -= 24;
			track_time->day++;
		}

		track_time->hour = hours;

		char *current_entry = malloc(max_line_length);
		snprintf(current_entry, max_line_length, track_time_template, 
				track_time->year,
				track_time->month,
				track_time->day,
				track_time->hour,
				track_time->second);
		printf("%s\n", current_entry);
		free(current_entry);
	}
}
