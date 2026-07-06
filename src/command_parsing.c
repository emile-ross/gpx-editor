#include "header.h"

int command_parsing(int num_args, char *arguments[])
{
	uint32_t final_time = 1;
	uint32_t interval_time = 0;
	struct maptime date = current_time();

	for (int i = 0; i < num_args; i++)
	{
		if (strcmp(arguments[i], "-i") == 0)
		{
			if (verbose)
			{
				printf("interval mode\n");
			}
			final_time = time_parsing(&i, num_args, arguments);
			printf("Interval time is: %u\n", interval_time);
		}
		else if (strcmp(arguments[i], "-t") == 0)
		{
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
	}

	uint8_t num_seconds, num_minutes, num_hours;
	stotime(final_time, &num_hours, &num_minutes, &num_seconds);

	printf("seconds: %d\nminutes: %d\nhours: %d\n", num_seconds, num_minutes, num_hours);
	forwards_write(&date, 9, interval_time);

	return 0;
}
