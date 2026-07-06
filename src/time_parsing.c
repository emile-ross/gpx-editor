#include "header.h"

void parsing_fail(char *time_type_msg);

uint32_t time_parsing(int *flag_r_index, int num_args, char *argument[])
{
	if (*flag_r_index > 255 || *flag_r_index < 0)
	{
		err("Invalid number of arguments");
	}

	uint8_t flag_r = (uint8_t)*flag_r_index;
	uint32_t duration = 0;
	uint8_t num_valid_args = 0;

	for (int i = flag_r; i < num_args; i++)
	{
		char *endptr = NULL;
		bool valid_arg = false;

		if (strcmp(argument[i], "-S") == 0)
		{
			i++; /* read ahead */

			/* no need to convert since this is already in seconds */
			long seconds = strtol(argument[i], &endptr, 10);
			if (conversion_check(endptr, argument[i], false))
				valid_arg = true;
			else
				parsing_fail("seconds");

			
			if (bound_check(seconds, 0, 59))
			{
				num_valid_args++;
				duration += (uint32_t)seconds;
			}
		}
		else if (strcmp(argument[i], "-M") == 0)
		{
			i++; /* read ahead */
			/* convert minutes to seconds */
			long minutes = strtol(argument[i], &endptr, 10);
			if (conversion_check(endptr, argument[i], false))
				valid_arg = true;
			else
				parsing_fail("minutes");

			if (bound_check(minutes, 0, 59))
			{
				num_valid_args++;
				duration += (uint32_t)(60 * minutes);
			}
		}
		else if (strcmp(argument[i], "-H") == 0)
		{
			i++; /* read ahead */
			/* convert hours to seconds */
			long hours = strtol(argument[i], &endptr, 10);
			if (conversion_check(endptr, argument[i], false))
				valid_arg = true;
			else
				parsing_fail("hours");

			if (bound_check((3600 * hours), 0, UINT32MAX))
			{
				num_valid_args++;
				duration += (uint32_t)(3600 * hours);
			}
		}

		if (valid_arg)
		{
			if (*endptr != '\0')
			{
				fprintf(stderr, "error converting \"%s\" to a number\n", endptr);
			}
		}
	}

	if (num_valid_args <= 0)
	{
		warn("No values were provided,\nTime set to 0 (default)");
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
