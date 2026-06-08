#include "header.h"

int time_parsing(int *flag_r_index, int num_args, char *argument[])
{
	int flag_r = *flag_r_index;

	int duration = 0;

	for (int i = flag_r; i < num_args; i++)
	{
		char *endptr = NULL;

		if (strcmp(argument[i], "-S") == 0)
		{
			i++; /* read ahead */
			duration += (int)strtol(argument[i], &endptr, 10);
		}
		else if (strcmp(argument[i], "-M") == 0)
		{
			i++; /* read ahead */
			int minutes = (int)strtol(argument[i], &endptr, 10);
			duration += (minutes * 60);
		}
		else if (strcmp(argument[i], "-H") == 0)
		{
			i++; /* read ahead */
			int hours = (int)strtol(argument[i], &endptr, 10);
			duration += (hours * 3600);
		}

		if (*endptr != '\0')
		{
			printf("error converting \"%s\" to a number\n", endptr);
		}
	}

	return duration;
}
