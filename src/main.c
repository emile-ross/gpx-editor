#include "header.h"
#include <stdarg.h>

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

	const char *message_template = "%s: %s"; /* program_name then the message */

	/* calculate message length */
	size_t message_len = 1 + (size_t)snprintf(NULL, 0, message_template, program_name, error_message);

	/* allocate memory for the message buffer */
	char *message = malloc(message_len);
	/* write to message buffer using snprintf */
	snprintf(message, message_len, message_template, program_name, error_message);

	fprintf(stderr, "\x1b[31m%s\x1B[0m\n", message);
	free(message);

	exit(1);
}

void warn(const char *restrict format, ...)
{
	va_list args;	/* use the ... */
	va_start(args, format);
	size_t msg_size = 1 + (size_t)vsnprintf(NULL, 0, format, args);
	va_end(args);

	char *warning_msg = malloc(msg_size);
	size_t ret = (size_t)vsnprintf(warning_msg, msg_size, format, args);
	if (ret > msg_size)
	{
		err("Warning message write failed");
	}
	
	printf("\x1B[1m\x1b[31m%s\x1B[0m\n", warning_msg);
	printf("\x1B[1mPress enter to continue\x1B[0m\n");

	free(warning_msg);

	getchar();
}

