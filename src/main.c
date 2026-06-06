#include "header.h"

char *program_name = "medit";

void err(const char *error_message);
int command_parsing(int num_args, char *arguments[]);

int main(int argc, char *argv[])
{
	if (!(argc > 1))
	{
		err("expected arguments");
	}

	command_parsing(argc, argv);

	return 0; /* c90 return value */
}


void err(const char *error_message)
{
	if (error_message == NULL)
	{
		exit(1);
	}

	char *message_template = "%s: %s"; /* program_name then the message */
	size_t message_len = 1 + (size_t)snprintf(NULL, 0, message_template, program_name, error_message);
	char *message = malloc(message_len);
	snprintf(message, message_len, message_template, program_name, error_message);

	printf("\x1b[31m%s\x1B[0m\n", message);

	exit(1);
}


int command_parsing(int num_args, char *arguments[])
{
	enum flag_type flag_type_arr[num_args]; /* initialise flag_type_arr used to assign a type of flag to a command index */

	int base_args = 1;	/* the index of the first possible valid argument (the command length "medit")*/
	
	for (int i = 0; i < base_args; i++)
	{
		flag_type_arr[i] = base_flag;
	}


	if (num_args == 2 || num_args == 4 )
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
				/* -t is total_time */

				/* this flag is not compatible with the "interval time" flag */
				if (!interval_time_mode)
				{
					flag_type_arr[i] = total_time;
					valid_editing_mode = true;
					valid_flag_temp = true;
				}
				else
				{
					valid_editing_mode = false;
				}
			}
			else if (strcmp(arguments[i], "-i") == 0)
			{
				if (!total_time_mode)
				{
					flag_type_arr[i] = interval_time;
					interval_time_mode = true;
					valid_editing_mode = true;
					valid_flag_temp = true;
				}
				else
				{
					valid_editing_mode = false;
				}
			}
			else if (strcmp(arguments[i], "-s") == 0)
			{
				valid_flag_temp = true;
				flag_type_arr[i] = start_time;
			}
			else if (strcmp(arguments[i], "-c") == 0)
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
				/*
				err(%s, arguments[i])
				*/
				err("Invalid command line argument");
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
