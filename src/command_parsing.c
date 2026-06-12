#include "header.h"

int command_parsing(bool used_args[], int num_args, char *arguments[])
{
	enum flag_type flag_type_arr[num_args]; /* initialise flag_type_arr used to assign a type of flag to a command index */

	int base_args = 1;	/* the index of the first possible valid argument (the command length "medit")*/
	
	for (int i = 0; i < base_args; i++)
	{
		flag_type_arr[i] = base_flag;
	}

	int num_usable_args = num_args - base_args;

	if (!num_usable_args % 2 == 0)
	{
		int base_arg_index = num_args - 1; /* different from useful_args_n because this is an index to the command */

		bool valid_editing_mode = false;
		/* checks if the argument is a valid flag 
		 * loop through all arguments */
		for (int i = base_args; i < base_arg_index; i++)
		{
			if (!used_args[i])
			{
				bool valid_flag_temp = false;
				if (strcmp(arguments[i], "-t") == 0)
				{
					time_parsing(&used_args, &i, num_args, arguments);
					used_args[i] = true;
					valid_flag_temp = true;
				}
				else if (strcmp(arguments[i], "-i") == 0)
				{
					used_args[i] = true;
					valid_flag_temp = true;
				}
				else if (strcmp(arguments[i], "--start-time") == 0)
				{
					used_args[i] = true;
					valid_flag_temp = true;
					flag_type_arr[i] = start_time;
				}
				else if (strcmp(arguments[i], "--cap-time") == 0)
				{
					used_args[i] = true;
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
