#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

char *program_name = "medit";

void err(const char *error_message);
int command_parsing(int num_args, char *arguments[]);

int main(int argc, char *argv[])
{
	if (!(argc > 1))
	{
		char *error_message_template = "%s expects arguments";
		size_t error_message_len = 1 + (size_t)snprintf(NULL, 0, error_message_template, program_name);
		char *error_message = malloc(error_message_len);
		snprintf(error_message, error_message_len, error_message_template, program_name);
		err(error_message);
	}

	command_parsing(argc, argv);

	return 0; /* c90 return value */
}


void err(const char *error_message)
{
	printf("\x1b[31m%s\x1B[0m\n", error_message);

	if (error_message == NULL)
	{
		exit(1);
	}
	exit(1);
}

int command_parsing(int num_args, char *arguments[])
{
	if (num_args == 2)
	{
		/* this means it is a simple command */
		printf("%s\n", arguments[1]);
	}
	else
	{
		err("Invalid number of arguments");
	}
	return 0;
}
