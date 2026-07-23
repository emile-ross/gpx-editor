#include "header.h"

void parsing_fail(char *time_type_msg);

int32_t time_parsing(uint8_t *flag_r_index, const uint8_t num_args, char *argument[])
{
	uint8_t flag_r = (uint8_t)*flag_r_index;
	int32_t duration = 0;
	uint8_t num_valid_args = 0;

	for (uint8_t i = flag_r; i < num_args; i++)
	{
		uint8_t next_index = i + 1;
		if (!(next_index < num_args))
		{
			err("Missing flags in time parsing\nUse flags for specifying the time \"-S\", \"-M\" or \"-H\"");
			break;
		}

		char *endptr = NULL;
		long date_arg = strtol(argument[next_index], &endptr, 10);
		Bool valid_arg = False;

		if (strcmp(argument[i], "-S") == 0)
		{
			i++; /* read ahead */

			/* no need to convert since this is already in seconds */
			if (conversion_check(endptr, argument[i], False))
				valid_arg = True;
			else
				parsing_fail("seconds");

			
			if (bound_check(date_arg, 0, 59))
			{
				num_valid_args++;
				duration += (int32_t)date_arg;
			}
		}
		else if (strcmp(argument[i], "-M") == 0)
		{
			i++; /* read ahead */
			/* convert minutes to seconds */
			if (conversion_check(endptr, argument[i], False))
				valid_arg = True;
			else
				parsing_fail("minutes");

			if (bound_check(date_arg, 0, 59))
			{
				num_valid_args++;
				duration += (int32_t)(60 * date_arg);
			}
		}
		else if (strcmp(argument[i], "-H") == 0)
		{
			i++; /* read ahead */
			/* convert hours to seconds */
			if (conversion_check(endptr, argument[i], False))
				valid_arg = True;
			else
				parsing_fail("hours");

			if (bound_check((3600 * date_arg), 0, UINT32MAX))
			{
				num_valid_args++;
				duration += (int32_t)(3600 * date_arg);
			}
		}

		if (valid_arg)
		{
			if (*(endptr) != '\0')
			{
				fprintf(stderr, "error converting \"%s\" to a number\n", endptr);
			}
		}
	}

	if (num_valid_args <= 0)
	{
		warn("No values were provided,\nTime set to 0 (default)");
	}

	bound_check(duration, (0-INT32MAX), INT32MAX);
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
