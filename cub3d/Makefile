MINILIBX_DIR = minilibx_linux
MINILIBX_LIB = mlx_Linux
SRCS = dda_test.c
OBJS = $(SRCS:%.c=%.o)
NAME = dda

CFLAGS := -Wall -Werror -Wextra
CC := cc

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBX_DIR) -l$(MINILIBX_LIB) -L/usr/lib -I$(MINILIBX_DIR) -fPIE -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -fPIE -I/usr/include -Iminilibx_linux -O3 -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
