# NAME = codexion
# CC = gcc
# CFLAGS = -g -lpthread -Wall -Wextra -Werror

# SRC = coders/codexion.c\
# 		coders/parse_agrs.c\
# 		coders/file_config.c\
# 		coders/start_threads.c\
# 		coders/init_dongles.c\
# 		coders/init_coders.c\
# 		coders/coder_routine.c\
# 		coders/time_us.c

# OBJ = $(SRC:%.c=%.o)

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: clean fclean re all

NAME = codexion
CC = gcc

CFLAGS = -g -Wall -Wextra -Werror 
# -pthread -fsanitize=thread

SRC = main.c \
		parse_agrs.c \
		file_config.c \
		start_threads.c \
		init_dongles.c \
		init_coders.c \
		coder_routine.c \
		utils.c \
		coder_actions.c \
		monitor.c \
		heap.c 

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean alld

.PHONY: clean fclean re all