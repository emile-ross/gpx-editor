#include "header.h"

void parsing_fail(char *time_type_msg);

uint32_t time_parsing(int *flag_r_index, int num_args, char *argument[])
{
	if (*flag_r_index > 255 || *flag_r_index < 0)
	{
		err("Invalid number of arguments");
	}

	uint8_t flag_r = (uint8_t)*flag_r_index;

	long duration = 0;

	for (int i = flag_r; i < num_args; i++)
	{
		char *endptr = NULL;
		bool valid_arg = false;

		if (strcmp(argument[i], "-S") == 0)
		{
			i++; /* read ahead */

			/* no need to convert since this is already in seconds */
			duration += strtol(argument[i], &endptr, 10);
			if (conversion_check(endptr, argument[i], false))
				valid_arg = true;
			else
				parsing_fail("seconds");

		}
		else if (strcmp(argument[i], "-M") == 0)
		{
			i++; /* read ahead */
			/* convert minutes to seconds */
			uint8_t minutes = (uint8_t)strtol(argument[i], &endptr, 10);
			duration += (long)(minutes * 60);
			if (conversion_check(endptr, argument[i], false))
				valid_arg = true;
			else
				parsing_fail("minutes");
		}
		else if (strcmp(argument[i], "-H") == 0)
		{
			i++; /* read ahead */
			/* convert hours to seconds */
			uint8_t hours = (uint8_t)strtol(argument[i], &endptr, 10);
			duration += (long)(hours * 3600);
			if (conversion_check(endptr, argument[i], false))
				valid_arg = true;
			else
				parsing_fail("hours");
		}

		if (valid_arg)
		{
			if (*endptr != '\0')
			{
				fprintf(stderr, "error converting \"%s\" to a number\n", endptr);
			}
		}
	}

	bound_check(duration, 0, UINT32MAX);
	uint32_t val = (uint32_t)duration;
	return val;
}


void parsing_fail(char *time_type_msg)
{
	/* combine the message with the time type (like seconds) 
	 * and then print it to stderr */
	fprintf(stderr, "Failed to convert input text to %s\n", time_type_msg);
	fprintf(stderr, "Only numbers are allowed\n");

	exit(1);
}
