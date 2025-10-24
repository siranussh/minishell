NAME = minishell

BUILT_SRC = builtin_utils.c list_utils.c free.c \
			echo.c pwd.c env.c env_parsing.c cd.c \
			unset.c \
			export_utils.c export_sort.c export_append.c export.c \
			exit_utils.c exit.c builtins.c

EXEC_SRC = find_cmd_path.c execute_single_cmd.c main.c

BUILT_SRCS = $(addprefix ./builtins/, $(BUILT_SRC))
EXEC_SRCS = $(addprefix ./execution/, $(EXEC_SRC))

BUILT_OBJS = $(BUILT_SRCS:.c=.o)
EXEC_OBJS = $(EXEC_SRCS:.c=.o)

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3 #-fsanitize=address

LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME) : $(BUILT_OBJS) $(EXEC_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I ./includes -I ./libft  $(BUILT_OBJS) $(EXEC_OBJS) -L ./libft -lft -o $(NAME)

$(LIBFT) :
	make -C ./libft all

%.o: %.c
	$(CC) $(CFLAGS) -I./includes -I./libft -c -o $@ $<

clean :
	make -C ./libft clean
	rm -f $(BUILT_OBJS)
	rm -f $(EXEC_OBJS)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
