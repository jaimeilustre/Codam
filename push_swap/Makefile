CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRCS			=	push_swap.c \
					push_rules.c \
					reverse_rotate_rules.c \
					rotate_rules.c \
					list_operations.c \
					swap_rules.c \
					chunk_creation.c \
					error_handling.c \
					input_validation.c \
					input_validation_utils.c \
					push_to_b.c \
					small_stacks.c \
					quicksort.c \
					chunk_utils.c \
					
OBJS			= $(SRCS:.c=.o)
NAME			= push_swap
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