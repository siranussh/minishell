#include "../includes/minishell.h"

int	get_redir_type(const char *token)
{
	if (!token)
		return (-1);
	if (ft_strcmp(token, "<") == 0)
		return (1);
	else if (ft_strcmp(token, "<<") == 0)
		return (2);
	else if (ft_strcmp(token, ">") == 0)
		return (3);
	else if (ft_strcmp(token, ">>") == 0)
		return (4);
	return (-1);
}