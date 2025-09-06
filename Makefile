NAME = minishell

SRC_FILES = utils.c echo.c pwd.c main.c

SRCS = $(addprefix ./builtins/, $(SRC_FILES))

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Werror -Wall -Wextra  -g3

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
