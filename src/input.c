#include "header.h"

uint16_t get_time(uint16_t lower_bound, uint16_t upper_bound, char *date_type, bool eight_bit_conversion)
{
	long date_input;
	int i = 0;


	uint16_t integer_max;
	if (eight_bit_conversion)
	{
		integer_max = 255;
	}
	else
	{
		integer_max = 65535;
	}

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
		else if (date_input < lower_bound ||  date_input > upper_bound)
		{
			fprintf(stderr, "Invalid date input\n");
		}
		else if (date_input < 0 || date_input > integer_max)
		{
			fprintf(stderr, "Invalid date input\n");
		}
		else
		{
			if (eight_bit_conversion)
			{
				return (uint8_t)date_input;
			}
			else
			{
				return (uint16_t)date_input;
			}
		}

		i++;
	}
}
