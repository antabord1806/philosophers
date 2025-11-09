
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread
SRC = src/threads.c
OBJ = $(SRC:.c=.o)
TARGET = threads.c \

# Regras
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re

