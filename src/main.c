#include "header.h"
#include <stdarg.h>

const char *program_name = "medit";

int main(int argc, char *argv[])
{
	if (!(argc > 1))
	{
		err("expected arguments");
	}

	if (argc > max_num_args)
	{
		err("Too many arguments max is %d", max_num_args);
	}

	command_parsing((uint8_t)argc, argv);

	return 0; /* c90 return value */
}

void err(const char *restrict format, ...)
{
	va_list args, copy;
	va_start(args, format);
	va_copy(copy, args);

	/* calculate the length of the message */
	size_t msg_body_size = 1 + (size_t)vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	/* allocate memory for the error message */
	char *base_error_msg = malloc(msg_body_size);
	/* check for a potential malloc() fail */
	if (base_error_msg == NULL)
	{
		fprintf(stderr, "%s: malloc() failed to allocate memory", program_name);
		exit(1);
	}
	/* write to buffer & compare return value with msg size calculated previously */
	size_t ret = (size_t)vsnprintf(base_error_msg, msg_body_size, format, args);
	va_end(args);

	if (ret > msg_body_size)
	{
		fprintf(stderr, "%s: Error message write failed", program_name);
		free(base_error_msg);
		exit(1);
	}
	const char *message_template = "%s: %s";	/* program_name then the message */

	size_t final_msg_size = 1 + (size_t)snprintf(NULL, 0, message_template, program_name, base_error_msg);
	char *error_msg = malloc(final_msg_size);
	if (error_msg == NULL)
	{
		free(base_error_msg);
		fprintf(stderr, "%s: malloc() failed to allocate memory", program_name);
	}
	/* write to buffer & compare return value with msg size calculated previously */
	ret = (size_t)snprintf(error_msg, final_msg_size, message_template, program_name, base_error_msg);
	free(base_error_msg);

	if (ret > final_msg_size)
	{
		fprintf(stderr, "%s: Error message write failed", program_name);
		free(error_msg);
		exit(1);
	}

	fprintf(stderr, "\x1b[31m%s\x1B[0m\n", error_msg);
	free(error_msg);

	exit(1);
}

void warn(const char *restrict format, ...)
{
	va_list args, copy;
	va_start(args, format);
	va_copy(copy, args);

	/* calculate the length of the message */
	size_t msg_size = 1 + (size_t)vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	/* allocate memory for the warning message */
	char *warning_msg = malloc(msg_size);
	if (warning_msg == NULL)
	{
		err("malloc() failed to allocate memory");
	}
	size_t ret = (size_t)vsnprintf(warning_msg, msg_size, format, args);
	va_end(args);

	if (ret > msg_size)
	{
		err("Warning message write failed");
	}
	
	printf("\x1B[1m\x1b[31m%s\x1B[0m\n", warning_msg);
	printf("\x1B[1mPress enter to continue\x1B[0m\n");

	free(warning_msg);

	getchar();
}

