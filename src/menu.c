#include "header.h"

void date_input(int *year, int *month, int *day, int *hour, int *minute, int *second)
{
	bool first_input = true;

	time_t default_time = time(NULL);
	
	struct tm *final_time = localtime(&default_time);

	final_time->tm_sec = 0;	/* seconds are set to 0 by default */

	int choice = -1;

	while (choice != 0)
	{
		if (first_input)
		{
			printf("The time is set to the current time by default\n");
		}

		char *time_string = malloc((size_t)max_time_len);
		strftime(time_string, (size_t)max_time_len, "%Y-%m-%d %H:%M:%S", final_time);
		
		printf("Date: %s\n", time_string);

		printf("Edit Year:   1\n");
		printf("Edit Month:  2\n");
		printf("Edit Day:    3\n");
		printf("Edit Hours:  4\n");
		printf("Edit Minute: 5\n");
		printf("Edit Second: 6\n");
		printf("\nDone:  0\n");

		scanf("%d", &choice);

	}
}
