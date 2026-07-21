#include "header.h"

int command_parsing(uint8_t num_args, char *arguments[])
{
	uint32_t final_time = 1;
	uint32_t time_interval_int = 0;
	struct maptime date = current_time();
	uint32_t num_waypoints = 0;
	uint8_t num_seconds, num_minutes, num_hours;

	for (uint8_t i = 0; i < num_args; i++)
	{
		uint8_t next_index = i + 1;
		Bool useless_flag = False;

		if (strcmp(arguments[i], "-i") == 0 || strcmp(arguments[i], "--interval") == 0)
		{
			if (verbose)
			{
				printf("interval mode\n");
			}
			time_interval_int = time_parsing(&i, num_args, arguments);
			printf("Interval time is: %u\n", time_interval_int);
		}
		else if (strcmp(arguments[i], "-t") == 0)
		{
			useless_flag = True;
			if (verbose)
			{
				printf("total time mode\n");
			}

			final_time = time_parsing(&i, num_args, arguments);
			printf("total time specified is: %u\n", final_time);
		}
		else if (strcmp(arguments[i], "--start-time") == 0 || strcmp(arguments[i], "-s") == 0)
		{
			/* get user input on the chosen time and store it in maptime date struct */
			date = date_input();
			size_t time_msg_size = timetotext(NULL, &date);	/* calculate buffer size */

			char *time_msg = malloc(time_msg_size);
			timetotext(time_msg, &date);
			printf("%s\n", time_msg);

			free(time_msg);

			if (verbose)
			{
				printf("start time\n");
			}
		}
		else if (strcmp(arguments[i], "--end-time") == 0 || strcmp(arguments[i], "-e") == 0)
		{
			useless_flag = True;

			/* get user input on the chosen time and store it in maptime date struct */
			date = date_input();
			size_t time_msg_size = timetotext(NULL, &date);	/* calculate buffer size */

			char *time_msg = malloc(time_msg_size);
			timetotext(time_msg, &date);
			printf("%s\n", time_msg);

			free(time_msg);

			if (verbose)
			{
				printf("end time\n");
			}
		}
		else if (strcmp(arguments[i], "-p") == 0 || strcmp(arguments[i], "--points") == 0 || 
				strcmp(arguments[i], "-w") == 0 || strcmp(arguments[i], "--waypoints") == 0)
		{
			char *endptr = NULL;
			long temp_points = strtol(arguments[next_index], &endptr, 10);
			if (*endptr != '\0')
			{
				err("Failed to convert points to integer");
			}

			bound_check(temp_points, 0, UINT32MAX);
			num_waypoints = (uint32_t)temp_points;
		}

		if (useless_flag)
		{
			/* display warning message */
			warn("The %s flag will not be used by the program", arguments[i]);
		}
	}

	stotime(final_time, &num_hours, &num_minutes, &num_seconds);

	printf("seconds: %d\nminutes: %d\nhours: %d\n", num_seconds, num_minutes, num_hours);
	forwards_write(&date, num_waypoints, time_interval_int);

	return 0;
}
