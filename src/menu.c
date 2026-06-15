#include "header.h"

void date_input(void)
{
	bool first_input = true;

	time_t default_time = time(NULL);
	
	struct tm *final_time = localtime(&default_time);

	final_time->tm_sec = 0;	/* seconds are set to 0 by default */

	int choice = -1;

	while (choice != 0)
	{
		clear();
		if (first_input)
		{
			printf("The time is set to the current time by default\n");
		}

		char *time_string = malloc((size_t)max_time_len);
		strftime(time_string, (size_t)max_time_len, "%Y-%m-%d %H:%M:%S", final_time);
		
		printf("Date: %s\n", time_string);

		printf("Edit Year:    1\n");
		printf("Edit Months:  2\n");
		printf("Edit Days:    3\n");
		printf("Edit Hours:   4\n");
		printf("Edit Minutes: 5\n");
		printf("Edit Seconds: 6\n");
		printf("\nSave and exit:  0\n");

		char buffer[100];
		char *endptr;
		long choice_temp = -1;


		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			printf("Failed to parse input.\n");
			exit(-1);
		}

		choice_temp = strtol(buffer, &endptr, 10);

		if (!(choice_temp > 6 || choice_temp < 0))
		{
			choice = (int)choice_temp;
		}

		switch (choice)
		{
			case 1:
				printf("Year\n");
				break;

			case 2:
				printf("Months\n");
				break;
				
			case 3:
				printf("Days\n");
				break;

			case 4:
				printf("Hours\n");
				break;

			default:
				printf("error\n");
				break;
		}
	}
}

long get_time(int upper_bound, int lower_bound, char *date_type)
{
	bool valid_date = false;
	long date_input;

	while (!valid_date)
	{
		clear();

		printf("Defining \"%s\"\n", date_type);

		printf("The number has to be between %d and %d\n", lower_bound, upper_bound);

		char input_buffer[128];
		char *endptr;

		if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
		{
			printf("Failed to parse input.\n");
			exit(-1);
		}
		else
		{
			valid_date = true;
		}

		date_input = strtol(input_buffer, &endptr, 10);

        	if (endptr == input_buffer)
		{
			fprintf(stderr, "No valid characters found");
			valid_date = false;
		}

		if (date_input < lower_bound ||  date_input > upper_bound)
		{
			fprintf(stderr, "Invalid date input\n");
			valid_date = false;
		}
	}

	return date_input;
}
