#include "header.h"

uint16_t get_time(uint16_t lower_bound, uint16_t upper_bound, char *date_type, bool eight_bit_conversion)
{
	long date_input;

	uint16_t integer_max;
	if (eight_bit_conversion)
	{
		integer_max = 255;
	}
	else
	{
		integer_max = 65535;
	}

	uint8_t i = 0;
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
			err("Failed to parse input.");
		}

		date_input = strtol(input_buffer, &endptr, 10);

		if (strcmp(endptr, input_buffer) == 0)
		{
			err("No valid characters found");
		}
        	if (*endptr != '\n' && *endptr != '\0')
		{
			err("Invalid input termination");
		}
		else if (date_input < lower_bound ||  date_input > upper_bound)
		{
			err("Invalid date input.");
		}
		else if (date_input < 0 || date_input > integer_max)
		{
			err("Invalid date input.");
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
