FLAGS = -Wconversion -Wall -Wextra -std=c99 -Wpedantic

base: 
	zig cc src/main.c -o medit $(FLAGS)

