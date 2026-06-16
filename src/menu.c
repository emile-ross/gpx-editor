#include "header.h"

void date_input(void)
{
	bool first_input = true;

	time_t default_time = time(NULL);
	
	struct tm *final_time = localtime(&default_time);

	final_time->tm_sec = 0;	/* seconds are set to 0 by default */

	int choice = -1;

	bool valid_choice = false;

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
			valid_choice = true;
		}

		long date = -1;
		switch (choice)
		{
			case 1:
				date = get_time(1900, 3000, "year");
				break;

			case 2:
				date = get_time(1, 12, "months");
				break;
				
			case 3:
				date = get_time(1, 31, "days");
				break;

			case 4:
				date = get_time(0, 23, "hours");
				break;

			case 5:
				date = get_time(0, 59, "minutes");
				break;

			case 6:
				date = get_time(0, 59, "seconds");
				break;

			default:
				valid_choice = false;
				break;
		}



		printf("%ld\n", date);

		if (valid_choice)
		{
			first_input = false;
		}
	}
}

long get_time(int lower_bound, int upper_bound, char *date_type)
{
	long date_input;

	int i = 0;
	while (1)
	{
		i++;
		clear();

		printf("%d\n", i);
		printf("Defining \"%s\"\n", date_type);

		printf("The number has to be between %d and %d\n", lower_bound, upper_bound);

		char input_buffer[128];
		char *endptr;

		if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
		{
			printf("Failed to parse input.\n");
		}

		date_input = strtol(input_buffer, &endptr, 10);

        	if (*endptr != '\n' && *endptr != '\0')
		{
			fprintf(stderr, "No valid characters found");
			getchar();
		}
		else if (date_input < lower_bound ||  date_input > upper_bound)
		{
			fprintf(stderr, "Invalid date input\n");
			getchar();
		}
		else
		{
			return date_input;
		}
	}
}
