CXX				= c++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	Functions.cpp
					
OBJS			= $(SRCS:.cpp=.o)
NAME			= dynamic

all:	$(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
