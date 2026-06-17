#include "header.h"

int command_parsing(int num_args, char *arguments[])
{
	int final_time = -1;

	for (int i = 0; i < num_args; i++)
	{
		if (strcmp(arguments[i], "-i") == 0)
		{
			if (verbose)
			{
				printf("interval mode\n");
			}
			int interval_time = time_parsing(&i, num_args, arguments);
			final_time = interval_time;
			printf("Interval time is: %d\n", interval_time);
		}
		else if (strcmp(arguments[i], "-t") == 0)
		{
			if (verbose)
			{
				printf("total time mode\n");
			}

			int total_time_input = time_parsing(&i, num_args, arguments);
			final_time = total_time_input;
			printf("total time specified is: %d\n", total_time_input);
		}
		else if (strcmp(arguments[i], "--start-time") == 0 || strcmp(arguments[i], "-s") == 0)
		{
			date_input();

			if (verbose)
			{
				printf("start time\n");
			}


		}
		else if (strcmp(arguments[i], "--end-time") == 0 || strcmp(arguments[i], "-e") == 0)
		{
			date_input();

			if (verbose)
			{
				printf("start time\n");
			}
		}
	}

	int num_seconds, num_minutes, num_hours;
	stotime(final_time, &num_hours, &num_minutes, &num_seconds);

	printf("seconds: %d\nminutes: %d\nhours: %d\n", num_seconds, num_minutes, num_hours);

	return 0;
}
