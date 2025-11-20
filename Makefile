NAME = minishell

BUILT_SRC = builtin_utils.c list_utils.c \
			echo.c pwd.c env.c env_parsing.c cd_utils.c cd.c \
			unset.c exit_utils.c exit.c \
			export_utils.c export_sort.c export_append.c export.c \
			builtins.c

EXEC_SRC = find_cmd_path.c heredoc.c execute_single_cmd.c join_cmd_tokens.c \
			child_parent_prcs.c setup_input_output.c \
			redir_utils.c \
			pipeline_utils.c execute.c \
			cmd_list_utils.c init_struct.c \
			execute_built_in.c get_status.c redir_utils_new.c execute_pipeline.c execute_new.c

SRC_TOKEN = create_token.c \
             handle_quotes.c \
             handle_quotes_2.c \
             token_pipe_utils.c \
             token_redir_utils.c \
             token_redir.c \
             token_utils.c \

SRC_EXPAND = expand_utils.c \
              expand_symb_utils.c \
              expand_var_utils.c \
              expand_exit_code.c \
              expand_libft_modifs.c \
			   expand.c \
			  expand_dollar_handler.c \
			  expand_dollar_handler2.c \

SRC_OTHER = minishell.c \
             error_handling.c \
             error_wrappers.c \
             utils.c \
             free.c \
             signals.c \
			 arr_list_handler.c \
			 arr_list_handler2.c \
			 free_env_exp.c \

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
CFLAGS = -Werror -Wall -Wextra -g3 #-fsanitize=address

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
