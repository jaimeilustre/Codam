CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	print_char.c \
					print_str.c \
					print_int.c \
					print_hex.c \
					print_ptr.c \
					
OBJS			= $(SRCS:.c=.o)

NAME			= libftprintf.a
LIBFT_DIR		= ./libft
LIBFT_LIB		= $(LIBFT_DIR)/libft.a

all:			$(LIBFT_LIB) $(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS) $(LIBFT_LIB)

$(LIBFT_LIB):
				$(MAKE) -C $(LIBFT_DIR)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re