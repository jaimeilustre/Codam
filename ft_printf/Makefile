CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	print_char.c \
					print_str.c \
					print_int.c \
					print_hex.c \
					
OBJS			= $(SRCS:.c=.o)

NAME			= libftprintf.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re