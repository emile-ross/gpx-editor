#include "header.h"

struct maptime date_input(void)
{
	bool first_input = true;

	time_t default_time = time(NULL);
	
	struct maptime *final_time = localtime(&default_time);

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

		int date = -1;
		switch (choice)
		{
			case 1:
				date = get_time(1900, 2147483647, "year");
				final_time->tm_year = date - 1900;
				break;

			case 2:
				date = get_time(1, 12, "months");
				final_time->tm_mon = date - 1;
				break;
				
			case 3:
				date = get_time(1, 31, "days");
				final_time->tm_mday = date;
				break;

			case 4:
				date = get_time(0, 23, "hours");
				final_time->tm_hour = date;
				break;

			case 5:
				date = get_time(0, 59, "minutes");
				final_time->tm_min = date;
				break;

			case 6:
				date = get_time(0, 59, "seconds");
				final_time->tm_sec = date;
				break;

			default:
				valid_choice = false;
				break;
		}
		printf("%d\n", date);

		if (valid_choice)
		{
			first_input = false;
		}
	}
	return *final_time;
}

void display_time(struct maptime *date)
{
	/* max_time_len is defined in the header file
	 * it is an arbitrary number of bytes since the strftime 
	 * function doesn't allow buffer size calculation 
	 * (like snprintf does) */ 
	char *time_message = malloc((size_t)max_time_len);
	strftime(time_message, (size_t)max_time_len, "%Y-%m-%d %H:%M:%S", date);
	
	printf("%s\n", time_message);
	free(time_message);
}

char *timetotext(struct maptime *date)
{
	char *time_format = "%u-%u-%u %u:%u:%u";

}
