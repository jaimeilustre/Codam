vpath %.c src/
.PHONY: all bonus clean fclean re debug

# LIBFT
LIBFT		:= libft/libft.a
LIBFT_DIR 	:= libft/

# COMPILE
CC			:= cc
C_FLAGS 	:= -Wall -Wextra -Werror
BIN 		:= bin/
DB_DIR 		:= debug/
C_DEBUG 	:= -fsanitize=address -g
C_INC		:= -I ./include -I ./$(LIBFT_DIR)include
C_LIB		:= -lreadline

# BINARIES
NAME		:= minishell
DB_NAME		:= db_minishell
SRCS 		:= main.c prompt.c command.c signal_utils.c ms_string.c ms_error.c
OBJS 		:= $(SRCS:%.c=$(BIN)%.o)
DB_OBJS 	:= $(SRCS:%.c=$(DB_DIR)%.o)

# COMPILE RULES

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(BIN) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(C_LIB) -o $(NAME)

$(BIN)%.o: %.c
	$(CC) $(C_FLAGS) -o $@ -c $< $(C_INC)

$(LIBFT):
	make -C $(LIBFT_DIR) all

debug: $(DB_NAME)

$(DB_NAME): $(DB_DIR) $(LIBFT) $(DB_OBJS)
	$(CC) $(C_DEBUG) $(DB_OBJS) $(LIBFT) $(C_LIB) -o $(DB_NAME)

$(DB_DIR)%.o: %.c
	$(CC) $(C_FLAGS) $(C_DEBUG) -o $@ -c $< $(C_INC)

# DIRECTORY RULES

$(BIN):
	mkdir $(BIN)

$(DB_DIR):
	mkdir $(DB_DIR)

# CLEAN AND RE RULES

clean:
	$(RM) $(OBJS)
	$(RM) $(DB_OBJS)

fclean:
	make -C $(LIBFT_DIR) fclean
	$(RM) -r $(BIN)
	$(RM) -r $(DB_DIR)
	$(RM) $(NAME)
	$(RM) $(DB_NAME)

re: fclean all
