#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct	s_cmd
{
	char	**args;
	char	*path;
	int		input_fd;
	int		output_fd;
} t_cmd;
# endif