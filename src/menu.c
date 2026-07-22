#include "header.h"

Bool match_input_type(enum input_types choice, struct maptime *date_target);

struct maptime date_input(void)
{
	Bool first_input = True;

	struct maptime final_time = current_time();

	final_time.second = 0;	/* seconds are set to 0 by default */

	long choice = -1;
	enum input_types input_type = undefined;
	Bool valid_choice = False;

	while (choice != exit_menu)
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

		printf("Edit Year:    %d\n", year);
		printf("Edit Months:  %d\n", month);
		printf("Edit Days:    %d\n", day);
		printf("Edit Hours:   %d\n", hour);
		printf("Edit Minutes: %d\n", minute);
		printf("Edit Seconds: %d\n", second);

		printf("\nSave and exit: %d\n", exit_menu);

		char buffer[100];
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			fprintf(stderr, "Failed to parse input.\n");
			exit(-1);
		}

		long choice_temp = -1;
		char *endptr = NULL;
		choice_temp = strtol(buffer, &endptr, 10);
		if (*endptr == '\n' && endptr != buffer)
		{
			if (!(choice_temp > 6 || choice_temp < 0))
			{
				choice = choice_temp;
				valid_choice = True;
			}

			if (valid_choice)
			{
				input_type = (enum input_types)choice;
				valid_choice = match_input_type(input_type, &final_time);

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

Bool match_input_type(enum input_types choice, struct maptime *date_target)
{
	uint16_t date = 0;
	switch (choice)
	{
		case year:
			date = get_time(0, 65535, "year", False);
			date_target->year = date;
			break;
	
		case month:
			date = get_time(1, 12, "months", True);
			date_target->month = (uint8_t)date;
			break;
			
		case day:
			date = get_time(1, 31, "days", True);
			date_target->day = (uint8_t)date;
			break;
	
		case hour:
			date = get_time(0, 23, "hours", True);
			date_target->hour = (uint8_t)date;
			break;
	
		case minute:
			date = get_time(0, 59, "minutes", True);
			date_target->minute = (uint8_t)date;
			break;
	
		case second:
			date = get_time(0, 59, "seconds", True);
			date_target->second = (uint8_t)date;
			break;

		case undefined:
		case exit_menu:
		default:
			return False;
			break;
	}
	return True;
}
