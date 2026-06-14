#include "header.h"

int command_parsing(int num_args, char *arguments[])
{
	for (int i = 0; i < num_args; i++)
	{
		if (strcmp(arguments[i], "-i") == 0)
		{
			if (verbose)
			{
				printf("interval mode\n");
			}
			int interval_time = time_parsing(&i, num_args, arguments);
		}
	}

	return 0;
}
