#include "header.h"

int command_parsing(int num_args, char *arguments[])
{
	unsigned long final_time = -1;

	for (int i = 0; i < num_args; i++)
	{
		if (strcmp(arguments[i], "-i") == 0)
		{
			if (verbose)
			{
				printf("interval mode\n");
			}
			unsigned long interval_time = time_parsing(&i, num_args, arguments);
			final_time = interval_time;
			printf("Interval time is: %lu\n", interval_time);
		}
		else if (strcmp(arguments[i], "-t") == 0)
		{
			if (verbose)
			{
				printf("total time mode\n");
			}

			unsigned long total_time_input = (unsigned long)time_parsing(&i, num_args, arguments);
			final_time = total_time_input;
			printf("total time specified is: %lu\n", total_time_input);
		}
		else if (strcmp(arguments[i], "--start-time") == 0 || strcmp(arguments[i], "-s") == 0)
		{
			/* get user input on the chosen time and store it in maptime date struct */
			struct maptime date = date_input();
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
			struct maptime date = date_input();
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

	return 0;
}
