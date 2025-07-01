CC = cc

CFLAGS = -Wall -Wextra -Werror 

NAME = so_long

SRC = src/so_long.c src/gnl.c src/parse1.c src/parse2.c src/cleaning.c src/gnl_utils.c src/lib_tools.c src/split.c src/build_map.c src/events_n_moves.c

OBJ = $(SRC:.c=.o)


define SOLONG_BANNER
	@echo "$(BLUE)"
	@echo "███████╗ ██████╗     ██╗      ██████╗ ███╗   ██╗ ██████╗ "
	@echo "██╔════╝██╔═══██╗    ██║     ██╔═══██╗████╗  ██║██╔════╝ "
	@echo "███████╗██║   ██║    ██║     ██║   ██║██╔██╗ ██║██║  ███╗"
	@echo "╚════██║██║   ██║    ██║     ██║   ██║██║╚██╗██║██║   ██║"
	@echo "███████║╚██████╔╝    ███████╗╚██████╔╝██║ ╚████║╚██████╔╝"
	@echo "╚══════╝ ╚═════╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ "
	@echo "$(RESET)"
endef

BLUE = \033[1;34m
RESET = \033[0m


all: $(NAME)

$(NAME): $(OBJ) 
	$(SOLONG_BANNER)
	$(CC)  $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

src/%.o: src/%.c so_long.h
	$(CC)  $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all
