#include "tokenization.h"

t_data *init(void)
{
    t_data *data;
    data = ft_calloc(sizeof(t_data), 1);
    if(!data)
        exit_error("minishell: malloc failed", 1);
    data->env = ft_calloc(sizeof(t_env), 1);
    if (!data->env)
        exit_error("minishell: malloc failed", 1);
    data->flags = ft_calloc(sizeof(t_flags), 1);
    if(!data->flags)
        exit_error("minishell: malloc failed", 1);
    return (data);
}

static void	print_tokens(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Command: %s\n", cmd->cmd);
		if (cmd->tokens)
		{
			i = 0;
			while (cmd->tokens[i])
			{
				printf("  token[%d]: %s\n", i, cmd->tokens[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
}

int	main(void)
{
	t_data	*data;
	char	*line;

	data = init();

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		if (!tokenize(data, &data->cmd, line))
		{
			printf("Tokenization failed.\n");
			continue;
		}
		if (data->cmd)
			print_tokens(data->cmd);
		data->cmd = NULL;
	}
	return (0);
}














