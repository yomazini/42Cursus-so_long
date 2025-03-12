CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = so_long
NAME_BONUS = so_long_bonus

SRC = src/so_long.c src/gnl.c src/parse1.c src/parse2.c src/cleaning.c src/gnl_utils.c src/lib_tools.c src/split.c src/build_map.c src/events_n_moves.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC)  $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

src/%.o: src/%.c so_long.h
	$(CC)  $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all