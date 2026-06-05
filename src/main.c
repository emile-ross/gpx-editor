#include <stdio.h>
#include <stdlib.h>

void err(const char *error_message);

int main(int argc, char *argv[])
{
	if (!(argc > 1))
	{
		err("Missing arguments");
	}
}


void err(const char *error_message)
{
	printf("\x1b[31m%s\x1B[0m\n", error_message);

	if (error_message == NULL)
	{
		exit(1);
	}
}
