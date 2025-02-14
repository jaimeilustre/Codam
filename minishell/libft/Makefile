vpath %.h include
vpath %.c src:src/get_next_line:src/ft_printf

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I include
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c \
ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line_bonus.c \
get_next_line.c ft_strchrnul.c ft_count.c ft_parse_printf.c ft_printf.c \
ft_printf_char.c ft_printf_helper.c ft_printf_hex.c ft_printf_int.c \
ft_printf_ptr.c ft_printf_size.c ft_printf_str.c ft_printf_uint.c ft_max.c

SRCS_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

BIN_DIR = ./bin/
DEP = libft.h get_next_line.h ft_printf.h
OBJS := $(SRCS:%.c=$(BIN_DIR)%.o)
OBJS_BONUS := $(SRCS_BONUS:%.c=$(BIN_DIR)%.o)

all: $(NAME)

$(NAME): $(BIN_DIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: all $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

$(BIN_DIR)%.o: %.c $(DEP)
	$(CC) $(INCLUDE) -c $(CFLAGS) $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -fv $(OBJS)
	rm -fv $(OBJS_BONUS)

fclean: clean
	rm -fv $(NAME)
	rm -df $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
