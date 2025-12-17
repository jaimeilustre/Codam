CXX				= c++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	main.cpp Bureaucrat.cpp AForm.cpp PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreationForm.cpp
					
OBJS			= $(SRCS:.cpp=.o)
					
OBJS			= $(SRCS:.cpp=.o)
NAME			= forms
all:	$(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re