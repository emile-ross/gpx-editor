#include "header.h"

void parsing_fail(char *time_type_msg);

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
			if (conversion_check(endptr, argument[i], false) == 0)
				valid_arg = true;
			else
				parsing_fail("seconds");

		}
		else if (strcmp(argument[i], "-M") == 0)
		{
			i++; /* read ahead */
			/* convert minutes to seconds */
			int minutes = (int)strtol(argument[i], &endptr, 10);
			duration += (minutes * 60);
			if (conversion_check(endptr, argument[i], false) == 0)
				valid_arg = true;
			else
				parsing_fail("minutes");
		}
		else if (strcmp(argument[i], "-H") == 0)
		{
			i++; /* read ahead */
			/* convert hours to seconds */
			int hours = (int)strtol(argument[i], &endptr, 10);
			duration += (hours * 3600);
			if (conversion_check(endptr, argument[i], false) == 0)
				valid_arg = true;
			else
				parsing_fail("hours");
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


void parsing_fail(char *time_type_msg)
{
	/* combine the message with the time type (like seconds) 
	 * and then print it to stderr */
	fprintf(stderr, "Failed to convert input text to %s\n", time_type_msg);
	fprintf(stderr, "Only numbers are allowed\n");
	exit(1);
}
