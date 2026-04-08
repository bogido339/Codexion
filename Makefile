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

CFLAGS = -g -Wall -Wextra -Werror -pthread -fPIE
LDFLAGS = -pthread -pie

SRC = coders/codexion.c \
		coders/parse_agrs.c \
		coders/file_config.c \
		coders/start_threads.c \
		coders/init_dongles.c \
		coders/init_coders.c \
		coders/coder_routine.c \
		coders/utils.c \
		coders/coder_actions.c \
		coders/monitor.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all