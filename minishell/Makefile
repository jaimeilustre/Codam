vpath %.c src/:src/builtin/:src/list/:src/env/:src/parser:src/exec:src/exec/redir:src/exec/expand:src/signals
.PHONY: all bonus clean fclean re debug valgrind

# LIBFT
LIBFT		:= libft/libft.a
DB_LIBFT	:= libft/db_libft.a
LIBFT_DIR 	:= libft/

# COMPILE
CC			:= cc
C_FLAGS 	:= -Wall -Wextra -Werror
BIN 		:= bin/
DB_DIR 		:= debug/
C_DEBUG 	:= -fsanitize=address,undefined,leak -g3 -fno-omit-frame-pointer
C_INC		:= -I ./include -I ./$(LIBFT_DIR)include
C_LIB		:= -lreadline

# BINARIES
NAME		:= minishell
DB_NAME		:= db_minishell
SRCS		:= ast.c builtin.c cd.c command.c echo.c env.c environment.c exec_cmd.c \
				exec_init.c exec_pipe.c exec_utils.c export.c find_cmd.c list.c \
				list_operations.c main.c ms_error.c ms_string.c parser.c \
				parser_utils.c prompt.c pwd.c redir.c redir_utils.c \
				ms_signals.c token.c tokenizer.c tokenizer_utils.c unset.c utils.c \
				validate.c env_init.c list_init.c exit.c stringbuilder.c \
				var_expansion.c quotes.c heredocs.c std_redir.c expansion.c wildcard.c \
				expansion_utils.c ast_builder.c sig_heredoc.c parenthesis.c
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
	@export LSAN_OPTIONS=suppressions=asan_minishell.supp

$(DB_NAME): $(DB_DIR) $(DB_LIBFT) $(DB_OBJS)
	$(CC) $(C_DEBUG) $(DB_OBJS) $(DB_LIBFT) $(C_LIB) -o $(DB_NAME)

$(DB_DIR)%.o: %.c
	$(CC) $(C_FLAGS) $(C_DEBUG) -o $@ -c $< $(C_INC)

$(DB_LIBFT):
	make -C $(LIBFT_DIR) debug

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=minishell.supp ./$(NAME)

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

re: fclean all debug
