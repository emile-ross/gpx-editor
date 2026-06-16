#include "header.h"


int get_time(int lower_bound, int upper_bound, char *date_type)
{
	long date_input;
	int i = 0;

	while (1)
	{
		clear();

		printf("Defining \"%s\"\n", date_type);
		printf("The number has to be between %d and %d\n", lower_bound, upper_bound);

		if (i > 5)
		{
			printf("Make sure your number respects the bounds specified above\n");
		}

		char input_buffer[128];
		char *endptr;

		if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
		{
			fprintf(stderr, "Failed to parse input.\n");
		}

		date_input = strtol(input_buffer, &endptr, 10);

        	if (*endptr != '\n' && *endptr != '\0')
		{
			fprintf(stderr, "No valid characters found\n");
		}
		else if (date_input < INT_MIN || date_input > INT_MAX)
		{
			fprintf(stderr, "Invalid date input\n");
		}
		else if (date_input < lower_bound ||  date_input > upper_bound)
		{
			fprintf(stderr, "Invalid date input\n");
		}
		else
		{
			return (int)date_input;
		}

		i++;
	}
}
