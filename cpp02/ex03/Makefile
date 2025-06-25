CC				= c++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	Fixed.cpp main.cpp Point.cpp bsp.cpp
					
OBJS			= $(SRCS:.cpp=.o)
NAME			= bsp

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re