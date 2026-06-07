FLAGS = -Wconversion -Wall -Wextra -std=c99 -Wpedantic

cmd = src/main.c src/command_parsing.c src/time_parsing.c -o medit 

base: 
	zig cc $(cmd) $(FLAGS) -Werror

install: base
	sudo cp -f medit /usr/bin/

gcc:
	gcc $(cmd)
