FLAGS = -Wconversion -Wall -Wextra -std=gnu99 -Wpedantic -Wshadow -Wswitch-enum -Wunreachable-code
Z = clang

SOURCE_DIR := src
filenames := write output current_time config menu input functions main command_parsing time_parsing

SRC_FILES := $(addsuffix .c, $(filenames))

FILES := $(addprefix $(SOURCE_DIR)/, $(SRC_FILES))

cmd = $(FILES) -o medit 

zig: 
	$(Z) $(cmd) $(FLAGS)
base: 
	$(Z) $(cmd) $(FLAGS) -Werror -g

install: base
	sudo cp -f medit /usr/bin/

gcc:
	gcc $(cmd) -Wall -Wextra -Wpedantic -std=c99 -Wconversion
