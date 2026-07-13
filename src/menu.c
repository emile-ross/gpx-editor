#include "header.h"

Bool match_input_type(int choice, struct maptime *date_target);

struct maptime date_input(void)
{
	Bool first_input = True;

	struct maptime final_time = current_time();

	final_time.second = 0;	/* seconds are set to 0 by default */

	int choice = -1;
	Bool valid_choice = False;

	while (choice != 0)
	{
		clear();

		if (first_input)
		{
			printf("The time is set to the current time by default\n");
		}

		size_t time_string_size = timetotext(NULL, &final_time);
		char *time_string = malloc((size_t)time_string_size);
		timetotext(time_string, &final_time);
		
		printf("Date: %s\n", time_string);
		free(time_string);

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
		if (*endptr == '\n' && endptr != buffer)
		{
			if (!(choice_temp > 6 || choice_temp < 0))
			{
				choice = (int)choice_temp;
				valid_choice = True;
			}

			if (valid_choice)
			{
				valid_choice = match_input_type(choice, &final_time);

				if (valid_choice)
				{
					first_input = False;
				}
			}
		}
	}

	return final_time;
}

size_t timetotext(char *target, struct maptime *date)
{
	char *time_format = "%u-%u-%u %u:%02u:%02u";

	size_t time_size = 1 + (size_t)snprintf(NULL, 0, time_format, 
			date->year,
			date->month, 
			date->day,
			date->hour,
			date->minute,
			date->second);
	if (target != NULL)
	{
		char *str = malloc(time_size);
		snprintf(str, time_size, time_format, 
			date->year,
			date->month, 
			date->day,
			date->hour,
			date->minute,
			date->second);
		strcpy(target, str);
		free(str);
	}
	return time_size;
}

Bool match_input_type(int choice, struct maptime *date_target)
{
	uint16_t date = 0;
	switch (choice)
	{
		case 1:
			date = get_time(0, 65535, "year", False);
			date_target->year = date;
			break;
	
		case 2:
			date = get_time(1, 12, "months", True);
			date_target->month = (uint8_t)date;
			break;
			
		case 3:
			date = get_time(1, 31, "days", True);
			date_target->day = (uint8_t)date;
			break;
	
		case 4:
			date = get_time(0, 23, "hours", True);
			date_target->hour = (uint8_t)date;
			break;
	
		case 5:
			date = get_time(0, 59, "minutes", True);
			date_target->minute = (uint8_t)date;
			break;
	
		case 6:
			date = get_time(0, 59, "seconds", True);
			date_target->second = (uint8_t)date;
			break;
	
		default:
			return False;
			break;
	}
	return True;
}
