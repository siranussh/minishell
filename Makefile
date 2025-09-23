NAME = minishell

SRC_FILES = utils.c list_utils.c echo.c pwd.c env.c env_parsing.c cd.c \
			unset.c main.c

SRCS = $(addprefix ./builtins/, $(SRC_FILES))

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3 #-fsanitize=address

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
