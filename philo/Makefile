
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = src/threads.c src/monitor.c
OBJ = $(SRC:.c=.o)
NAME = philo

# Regras
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all all

.PHONY: all clean fclean re

