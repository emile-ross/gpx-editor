#include "header.h"

int time_parsing(bool *used_args[], int *flag_r_index, int num_args, char *argument[])
{
	int flag_r = *flag_r_index;

	int duration = 0;

	for (int i = flag_r; i < num_args; i++)
	{
		char *endptr = NULL;
		bool valid_arg = false;

		if (strcmp(argument[i], "-S") == 0)
		{
			*used_args[i] = true;	/* mark as used */
			i++; /* read ahead */
			*used_args[i] = true;	/* mark as used */
			duration += (int)strtol(argument[i], &endptr, 10);
			valid_arg = true;
		}
		else if (strcmp(argument[i], "-M") == 0)
		{
			*used_args[i] = true;	/* mark as used */
			i++; /* read ahead */
			int minutes = (int)strtol(argument[i], &endptr, 10);
			duration += (minutes * 60);
			valid_arg = true;
		}
		else if (strcmp(argument[i], "-H") == 0)
		{
			*used_args[i] = true;	/* mark as used */
			i++; /* read ahead */
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
