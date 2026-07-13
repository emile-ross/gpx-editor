typedef struct maptime
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} MapTime;

typedef struct
{
	Bool interval_specified;
	Bool start_time_specified;
	Bool end_time_specified;
}  output_arguments_bl;

struct maptime current_time(void);
struct maptime date_input(void);
