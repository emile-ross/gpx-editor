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
			valid_arg = true;
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


int conversion_check(const char *endptr, const char *input_string, const bool newline)
{
	if (!ignore_errors)
	{
		if (*endptr == '\0')
		{
			return 0;
		}

		if (strcmp(endptr, input_string) == 0)
		{
			fprintf(stderr, "No valid characters were found\n");
			exit(-1);
			return 1;
		}

		if (newline)
		{
			if (*endptr == '\n')
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}

