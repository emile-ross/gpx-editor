#include "header.h"

const char *program_name = "medit";

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

	/* calculate message length */
	size_t message_len = 1 + (size_t)snprintf(NULL, 0, message_template, program_name, error_message);

	/* allocate memory for the message buffer */
	char *message = malloc(message_len);
	/* write to message buffer using snprintf */
	snprintf(message, message_len, message_template, program_name, error_message);

	fprintf(stderr, "\x1b[31m%s\x1B[0m\n", message);

	exit(1);
}
