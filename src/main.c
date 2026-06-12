#include "header.h"

char *program_name = "medit";

int main(int argc, char *argv[])
{
	bool used_args[argc];
	for (int i = 0; i < argc; i++)
	{
		used_args[i] = false;
	}

	used_args[0] = true;

	if (!(argc > 1))
	{
		err("expected arguments");
	}

	command_parsing(used_args, argc, argv);

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
