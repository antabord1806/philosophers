
CC = cc 
CFLAGS = -Wall -Wextra -Werror -pthread 
SRC = src/p_threads.c src/p_monitor.c src/p_routine.c src/p_meal_check.c src/p_single_philo.c 
OBJ = $(SRC:.c=.o)
NAME = philo

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

