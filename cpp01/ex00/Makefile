CC				= c++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	main.cpp Zombie.cpp newZombie.cpp randomChump.cpp
					
OBJS			= $(SRCS:.cpp=.o)
NAME			= zombie

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re