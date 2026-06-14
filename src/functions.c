#include "header.h"

void stotime(int total_seconds, int *hours, int *minutes, int *seconds)
{
	int hours_remainder = total_seconds % 3600;
	printf("remainder = %d\n", hours_remainder);
	int minutes_remainder = total_seconds % 60;
	printf("Number of minutes: %d\n", minutes_remainder);
}

