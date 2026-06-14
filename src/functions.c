#include "header.h"

void stotime(int total_seconds, int *hours, int *minutes, int *seconds)
{
	int seconds_remainder = total_seconds % 60;
	*seconds = seconds_remainder;

	int minutes_pre_remainder = total_seconds - seconds_remainder;
	int minutes_remainder = minutes_pre_remainder % 3600;
	*minutes = minutes_remainder / 60;

	int hours_temp = minutes_pre_remainder - minutes_remainder;
	*hours = hours_temp / 3600;
}

