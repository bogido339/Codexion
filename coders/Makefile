NAME = codexion
CC = cc

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