FLAGS = -Wconversion -Wall -Wextra -std=gnu99 -Wpedantic -Wshadow -Wswitch-enum -Wunreachable-code
CC = gcc

SOURCE_DIR := src
filenames := write output current_time config menu input functions main command_parsing time_parsing

SRC_FILES := $(addsuffix .c, $(filenames))

FILES := $(addprefix $(SOURCE_DIR)/, $(SRC_FILES))

CMD = $(CC) $(FILES) -o medit 

zig: 
	$(CMD) $(FLAGS)
base: 
	$(CMD) $(FLAGS) -g -Werror

install: base
	sudo cp -f medit /usr/bin/

gcc:
	$(CMD) $(FLAGS)
