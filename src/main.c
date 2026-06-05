#include <stdio.h>
#include <stdlib.h>

void err(const char *error_message);
int command_parsing(int num_args, char *arguments[]);

int main(int argc, char *argv[])
{
	command_parsing(argc, argv);
	if (!(argc > 1))
	{
		err("Missing arguments");
	}


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
