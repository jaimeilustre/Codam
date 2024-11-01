CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	ft_print_char.c \
					ft_print_str.c \
					ft_print_int.c \
					ft_print_hex.c \
					ft_print_ptr.c \
					ft_print_unsigned.c \
					ft_printf.c \
					
OBJS			= $(SRCS:.c=.o)

NAME			= libftprintf.a
LIBFT_DIR		= ./libft
LIBFT_LIB		= $(LIBFT_DIR)/libft.a

all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	cp $(LIBFT_LIB) $(NAME)
	ar rcs $(NAME) $(OBJS)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re:	fclean all

.PHONY:	all clean fclean re