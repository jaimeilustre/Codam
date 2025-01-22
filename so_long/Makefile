CC				= cc
RM				= rm -f
CFLAGS			= -I ~/MLX42/include -Wall -Wextra -Werror 

SRCS			=	map_parsing.c \
					map_rendering.c \
					map_validation.c \
					path_validation.c \
					player_movement.c \
					so_long.c \
					utils.c \
					
OBJS			= $(SRCS:.c=.o)

NAME			= so_long
LIBFT_DIR		= ./libft
LIBFT_LIB		= $(LIBFT_DIR)/libft.a
MLX				= ~/MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT_LIB) -o $(NAME)

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