#include "../includes/minishell.h"

int	tokenize(t_data *data, t_cmd **cmd, char *read_line)
{
	int		i;
	t_cmd	*temp;
	char	**lines;

	i = 0;
	lines = NULL;
	data->total_chars = 0;
	if (parse_line(&data, read_line, &lines))
		return (0);
	*cmd = build_cmd(data, lines[0]);
	expand(cmd, data);
	while (++i <= data->flags->pipe)
	{
		data->total_chars = 0;
		temp = build_cmd(data, lines[i]);
		expand(&temp, data);
		(last_cmd(cmd))->next = temp;
		temp = temp->next;
	}
	while (i--)
		free(lines[i]);
	free(lines);
	return (1);
}

