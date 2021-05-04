NAME = fdf
SRC = color_op.c draw.c globs.c main.c mtx.c parsing.c \
			data_setup.c keyev.c more_mtx.c mtx_op.c save_image.c
SRCDIR = src/
OBJ = $(SRC:.c=.o)
OBJDIR = obj/
INC = includes/
INCLIBFT = libft/includes
LIBFT = libft/libft.a
FLAGS = -Wall -Wextra -Werror

SETCYAN = \033[1;36m
UNSETCOLOR = \033[0m

.PHONY: all clean fclean re notify makeobj

all: $(NAME)

notify:
	@[ -d obj ] || mkdir obj
	@printf "$(SETCYAN)Updating object files...$(UNSETCOLOR)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c | notify
	@gcc $(FLAGS) -c $< -I $(INC) -I $(INCLIBFT) -I minilibx -o $@

$(NAME): $(addprefix $(OBJDIR), $(OBJ))
	@make -C libft
	gcc $^ $(LIBFT) $(FLAGS) -Lminilibx -lpng -lmlx -lX11 -lXext -o $(NAME)

clean:
	@make clean -C libft
	rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C libft
	rm -rf $(NAME)

re: fclean all
