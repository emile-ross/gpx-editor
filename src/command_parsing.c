#include "header.h"

int command_parsing(int num_args, char *arguments[])
{
	enum flag_type flag_type_arr[num_args]; /* initialise flag_type_arr used to assign a type of flag to a command index */

	int base_args = 1;	/* the index of the first possible valid argument (the command length "medit")*/
	
	for (int i = 0; i < base_args; i++)
	{
		flag_type_arr[i] = base_flag;
	}

	int num_usable_args = num_args - base_args;

	if (num_usable_args % 2 == 0)
	{
		int base_arg_index = num_args - 1; /* different from useful_args_n because this is an index to the command */

		bool valid_editing_mode = false;
		bool interval_time_mode = false;
		bool total_time_mode = false;

		/* checks if the argument is a valid flag 
		 * loop through all arguments */
		for (int i = base_args; i < base_arg_index; i++)
		{
			bool valid_flag_temp = false;
			if (strcmp(arguments[i], "-t") == 0)
			{
				time_parsing(&i, base_arg_index, arguments);
				/* -t is total_time
				 * this flag is not compatible with the "interval time" flag */
				int time_specific_flags = 0;

				for (int j = i; j < base_arg_index; j++)
				{
					if (strcmp(arguments[j], "-S") == 0)
					{
						time_specific_flags += 2;
					}
					else if (strcmp(arguments[j], "-M") == 0)
					{
						time_specific_flags += 2;
					}
					else if (strcmp(arguments[j], "-H") == 0)
					{
						time_specific_flags += 2;
					}
				}

				if (time_specific_flags > 6)
				{
					err("Too many arguments");
				}

				valid_flag_temp = true;

				if (!interval_time_mode)
				{
					flag_type_arr[i] = total_time;
					valid_editing_mode = true;
					total_time_mode = true;
				}
				else
				{
					valid_editing_mode = false;
				}
			}
			else if (strcmp(arguments[i], "-i") == 0)
			{
				/* i is used here since we start looking for -S flags from the -i flag to the right */
				int time_specific_flags = 0;

				for (int j = i; j < base_arg_index; j++)
				{
					if (strcmp(arguments[j], "-S") == 0)
					{
						time_specific_flags += 2;
					}
					else if (strcmp(arguments[j], "-M") == 0)
					{
						time_specific_flags += 2;
					}
				}

				if (time_specific_flags > 4)
				{
					err("Too many arguments");
				}

				if (!total_time_mode)
				{
					flag_type_arr[i] = interval_time;

					char *endptr;
					i++;
					int interval_time_seconds = (int)strtol(arguments[i], &endptr, 10);

					if (*endptr == '\0')
					{
						valid_flag_temp = true;
						interval_time_mode = true;
						printf("%d\n", interval_time_seconds);
						valid_editing_mode = true;
					}
					else if (strcmp(arguments[i], endptr) == 0)
					{
						printf("You entered no valid numbers\n");
					}
				}
				else
				{
					valid_editing_mode = false;
				}
			}
			else if (strcmp(arguments[i], "--start-time") == 0)
			{
				valid_flag_temp = true;
				flag_type_arr[i] = start_time;
			}
			else if (strcmp(arguments[i], "--cap-time") == 0)
			{
				valid_flag_temp = true;
				flag_type_arr[i] = cap_time;
			}
			else
			{
				/* argument does not match any known flags */
				flag_type_arr[i] = unknown_flag;
			}
			
			if (!valid_flag_temp)
			{
				/* produce error message with the invalid flag */
				char *message_template = "Invalid flag: %s\nat index: %d";
				size_t message_size = 1 + (size_t)snprintf(NULL, 0, message_template, arguments[i], i);

				char *err_message = malloc(message_size);
				snprintf(err_message, message_size, message_template, arguments[i], i); /* write to the memory */

				err(err_message); /* display error message */

				exit(1);

				free(err_message);	/* no need to free since the program crashes */
			}
		}

		if (valid_editing_mode)
		{
			printf("Valid command\n");
		}
	}
	else
	{
		err("Invalid number of arguments");
	}
	return 0;
}
