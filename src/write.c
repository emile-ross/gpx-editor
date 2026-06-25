#include "header.h"

void forwards_write(struct maptime *track_time)
{
	uint16_t year = track_time->year;
	uint8_t month = track_time->month;
	uint8_t day = track_time->day;
	uint8_t hour = track_time->hour;
	uint8_t minute = track_time->minute;
	uint8_t second = track_time->second;

	const char *track_time_template = "<when>%u-%u-%uT%u:%u:%uZ</when>";
}
