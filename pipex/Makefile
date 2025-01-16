CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	pipex.c \
					command_execution.c \
					command_parsing.c \
					error_handling.c \
					file_handling.c \
					free_memory.c \
					process_management.c \
					
OBJS			= $(SRCS:.c=.o)

NAME			= pipex
LIBFT_DIR		= ./libft
LIBFT_LIB		= $(LIBFT_DIR)/libft.a

all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re:	fclean all

.PHONY:	all clean fclean re