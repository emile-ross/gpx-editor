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
