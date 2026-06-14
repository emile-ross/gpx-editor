FLAGS = -Wconversion -Wall -Wextra -std=c99 -Wpedantic
Z = zig cc

cmd = src/functions.c src/main.c src/command_parsing.c src/time_parsing.c -o medit 

zig: 
	$(Z) $(cmd) $(FLAGS)
base: 
	$(Z) $(cmd) $(FLAGS) -Werror

install: base
	sudo cp -f medit /usr/bin/

gcc:
	gcc $(cmd)
