CLIENT_NAME = client
SERVER_NAME = server

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a

all: $(CLIENT_NAME) $(SERVER_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft/

$(CLIENT_NAME): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(CLIENT_NAME)

$(SERVER_NAME): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(SERVER_NAME)

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	@make clean -C libft/

fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	@make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re