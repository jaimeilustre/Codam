CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	parser.c
					
OBJS			= $(SRCS:.c=.o)
NAME			= philo

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C

re:	fclean all

.PHONY:	all clean fclean re