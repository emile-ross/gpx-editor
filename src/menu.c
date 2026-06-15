#include "header.h"

void date_input(int *year, int *month, int *day, int *hour, int *minute, int *second)
{
	bool first_input = true;

	time_t default_time = time(NULL);

	struct tm *final_time = localtime(&default_time);

	if (first_input)
	{
		printf("The time is set to the current time by default\n");
	}

	char *time_string = malloc((size_t)max_time_len);
	strftime(time_string, (size_t)max_time_len, "%Y-%m-%d %H:%M:%S", final_time);
	
	printf("Date: %s\n", time_string);

}
