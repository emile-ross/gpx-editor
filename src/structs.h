typedef struct maptime
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} MapTime;

struct maptime current_time(void);
struct maptime date_input(void);

struct write_cmd_args
{
	Bool interval_time;
	Bool starting_time;
	Bool ending_time;
	Bool num_waypoints;
};

struct write_arguments
{
	uint32_t num_waypoints;
	int32_t time_interval;
};
