# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 13:09:35 by lkallio           #+#    #+#              #
#    Updated: 2021/04/18 14:12:30 by lkallio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC =  ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_realloc.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstdelone.c ft_lstnew.c ft_itrn.c \
		ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_stern.c \
		ft_memdel.c ft_memmove.c ft_memrchr.c ft_memset.c ft_putchar.c ft_strass.c \
		ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_append.c ft_intass.c \
		ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_stpncpy.c ft_strchrn.c ft_ptern.c \
		ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strpush.c \
		ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strstrj.c \
		ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strtol.c \
		ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
		ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
		ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstiter.c ft_lstmap.c ft_filetostr.c \
		ft_lstadd.c ft_lstdel.c ft_iswspace.c ft_strndup.c ft_strcdup.c ft_strex.c \
		ft_strconchr.c ft_strconchrlen.c ft_strcondup.c ft_strconchrrlen.c \
		ft_strchrlen.c ft_strlcpy.c ft_strnjoin.c ft_strcjoin.c get_next_line.c \
		pf_dbl_data.c pf_ft_printf.c pf_handle_buffer.c pf_handle_double.c \
		pf_handle_ints.c pf_handle_n_str.c pf_utils.c pf_write_double.c pf_write_ints.c
FLAGS = -Wall -Wextra -Werror
SRCDIR = src/
OBJ = $(SRC:.c=.o)
OBJDIR = obj/
INC = includes

.PHONY: all clean fclean re

all: $(NAME)

notify:
	@[ -d obj ] || mkdir obj
	@printf "\033[1;35mMaking printf...\033[0m\n"

$(OBJDIR)%.o: $(SRCDIR)%.c | notify
	@gcc $(FLAGS) -c $< -I $(INC) -o $@

$(NAME): $(addprefix $(OBJDIR), $(OBJ))
	@ar rcs $(NAME) $?

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
