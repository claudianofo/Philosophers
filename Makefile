NAME = philo
CFLAGS = -Wall -Werror -Wextra -g -O0
SRC_PATH = sources/
OBJ_PATH = objects/
SOURCES = main.c input.c utils.c
SRCS	= $(addprefix $(SRC_PATH), $(SOURCES))
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
OBJS	= $(addprefix $(OBJ_PATH), $(OBJECTS))
INCS	= -I ./includes/

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re