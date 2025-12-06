NAME = minishell

BUILT_SRC = builtin_utils.c list_utils.c \
			builtins.c \
			cd_utils.c cd.c \
			echo.c \
			env_parsing.c env.c \
			exit_utils.c exit.c \
			export_append.c export_sort.c export_utils.c export.c \
			pwd.c \
			unset.c \
			shlvl.c

EXEC_SRC = cmd_list_utils.c init_struct.c \
			find_cmd_path.c join_cmd_tokens.c \
			redir_utils.c \
			heredoc.c \
			parse_redirs.c setup_redirs.c \
			pipeline_utils.c \
			execute_built_in.c \
			execute_single_cmd.c \
			execute_pipeline.c \
			execute.c

SRC_TOKEN = create_token.c \
			 handle_quotes.c \
			 handle_quotes_2.c \
			 token_pipe_utils.c \
			 token_redir_utils.c \
			 token_redir.c \
			 token_redir2.c \
			 token_redir3.c \
			 token_utils.c \
			 token_utils_2.c \
			 build_redir_tokens.c \
			 tokenize.c \

SRC_EXPAND = expand_utils.c \
			 expand_symb_utils.c \
			 expand_var.c \
			 expand_var_utils.c \
			 expand_exit_code.c \
			 expand_libft_modifs.c \
			 expand.c \
			 expand_dollar_handler.c \

SRC_OTHER = minishell.c \
			 error_handling.c \
			 error_wrappers.c \
			 utils.c \
			 free_cmd.c \
			 free_env_exp.c \
			 free.c \
			 signals.c \
			 arr_list_handler.c \
			 arr_list_handler2.c \

TOKEN_DIR = tokenization
EXPAND_DIR = expansion
OBJ_DIR = obj

BUILT_DIR = builtins
EXEC_DIR = execution

OBJ_TOKEN  = $(addprefix $(OBJ_DIR)/$(TOKEN_DIR)/,$(SRC_TOKEN:.c=.o))
OBJ_EXPAND = $(addprefix $(OBJ_DIR)/$(EXPAND_DIR)/,$(SRC_EXPAND:.c=.o))
OBJ_OTHER  = $(addprefix $(OBJ_DIR)/,$(SRC_OTHER:.c=.o))

OBJ_EXEC = $(addprefix $(OBJ_DIR)/$(EXEC_DIR)/,$(EXEC_SRC:.c=.o))
OBJ_BUILT = $(addprefix $(OBJ_DIR)/$(BUILT_DIR)/,$(BUILT_SRC:.c=.o))

OBJ = $(OBJ_TOKEN) $(OBJ_EXPAND) $(OBJ_OTHER) $(OBJ_BUILT) $(OBJ_EXEC)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -I ./includes -I ./libft $(OBJ) -L ./libft -lft -lreadline -o $(NAME)

$(LIBFT):
	make -C ./libft all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I ./includes -I ./libft -c $< -o $@

clean:
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
