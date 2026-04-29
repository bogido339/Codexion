NAME = codexion
CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

SRC = coders/main.c \
	coders/parse_args.c \
	coders/init.c \
	coders/threads_manager.c \
	coders/simulation_state.c \
	coders/coder_states.c \
	coders/dongle_manager.c \
	coders/heap_manager.c \
	coders/scheduler.c \
	coders/routine.c \
	coders/monitor.c \
	coders/coder_stats.c \
	coders/time_io.c \
	coders/deadlock.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all