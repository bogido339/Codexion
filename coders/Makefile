NAME = codexion
CC = cc

CFLAGS = -g -Wall -Wextra -Werror -lpthread
# -pthread -fsanitize=thread

SRC = main.c \
	parse_args.c \
	init.c \
	threads_manager.c \
	simulation_state.c \
	coder_states.c \
	dongle_manager.c \
	heap_manager.c \
	scheduler.c \
	routine.c \
	monitor.c \
	coder_stats.c \
	time_io.c

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

re: fclean all

.PHONY: clean fclean re all