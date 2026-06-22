#include "header.h"

int time_parsing(int *flag_r_index, int num_args, char *argument[])
{
	int flag_r = *flag_r_index;

	int duration = 0;

	for (int i = flag_r; i < num_args; i++)
	{
		char *endptr = NULL;
		bool valid_arg = false;

		if (strcmp(argument[i], "-S") == 0)
		{
			i++; /* read ahead */

			/* no need to convert since this is already in seconds */
			duration += (int)strtol(argument[i], &endptr, 10);
			if (conversion_check(&endptr, argument[i], false) == 0)
			{
				valid_arg = true;
			}
			else
			{
				fprintf(stderr, "Failed to convert input to time\n");
				exit(1);
			}

		}
		else if (strcmp(argument[i], "-M") == 0)
		{
			i++; /* read ahead */
			/* convert minutes to seconds */
			int minutes = (int)strtol(argument[i], &endptr, 10);
			duration += (minutes * 60);
			valid_arg = true;
		}
		else if (strcmp(argument[i], "-H") == 0)
		{
			i++; /* read ahead */
			/* convert hours to seconds */
			int hours = (int)strtol(argument[i], &endptr, 10);
			duration += (hours * 3600);
			valid_arg = true;
		}

		if (valid_arg)
		{
			if (*endptr != '\0')
			{
				printf("error converting \"%s\" to a number\n", endptr);
			}
		}
	}

	return duration;
}

