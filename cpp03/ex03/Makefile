CC				= c++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	ClapTrap.cpp main.cpp ScavTrap.cpp FragTrap.cpp DiamondTrap.cpp
					
OBJS			= $(SRCS:.cpp=.o)
NAME			= diamondtrap
all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re