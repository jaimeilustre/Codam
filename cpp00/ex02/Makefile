CC				= c++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	Account.cpp tests.cpp
					
OBJS			= $(SRCS:.cpp=.o)
NAME			= account

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re