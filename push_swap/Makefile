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
					stack_utils.c \
					greedy_calculation.c \
					small_stacks.c \
					chunk_creation_utils.c \
					chunk_operations.c \
					
OBJS			= $(SRCS:.c=.o)
NAME			= push_swap
LIBFT_DIR		= ./libft
LIBFT_LIB		= $(LIBFT_DIR)/libft.a

BONUS_SRCS		=	checker.c \
					get_next_line.c \

BONUS			= checker
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

FILTERED_OBJS	= $(filter-out push_swap.o, $(OBJS))

all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

bonus:	$(BONUS)

$(BONUS): $(BONUS_OBJS) $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(FILTERED_OBJS) $(LIBFT_LIB) -o $(BONUS)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(BONUS_OBJS) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME) $(BONUS)
	$(MAKE) fclean -C $(LIBFT_DIR)

re:	fclean all

.PHONY:	all clean fclean re