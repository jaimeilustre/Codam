CXX				= c++
RM				= rm -f
CXXFLAGS		= -Wall -Wextra -Werror

SRCS			= Functions.cpp main.cpp
					
OBJS			= $(SRCS:.cpp=.o)
NAME			= dynamic

all:	$(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
