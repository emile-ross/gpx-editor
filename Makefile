FLAGS = -Wconversion -Wall -Wextra -std=c99 -Wpedantic -Wshadow
Z = zig cc

SOURCE_DIR := src
SRC_FILES := menu.c input.c functions.c main.c command_parsing.c time_parsing.c
FILES := $(addprefix $(SOURCE_DIR)/, $(SRC_FILES))

cmd = $(FILES) -o medit 

zig: 
	$(Z) $(cmd) $(FLAGS)
base: 
	$(Z) $(cmd) $(FLAGS) -Werror

install: base
	sudo cp -f medit /usr/bin/

gcc:
	gcc $(cmd)
