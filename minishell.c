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
                char *unquoted = unqoute_str(cmd->tokens[i]);
                free(cmd->tokens[i]);
                cmd->tokens[i] = unquoted;
				printf("  token[%d]: %s\n", i, cmd->tokens[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;

    (void) argc;
    (void) argv;
	data = init();
    data->env->env = envp;
    data->env->num_env = 0;
while (envp[data->env->num_env])
    data->env->num_env++;

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
        data->flags->pipe = 0;
		data->flags->quote = 0;
		data->flags->has_special = 0;
		if (!tokenize(data, &data->cmd, line))
		{
			printf("Tokenization failed.\n");
			continue;
		}
		if (data->cmd)
			print_tokens(data->cmd);
		data->cmd = NULL;
	}
    free(data->env);
	free(data->flags);
	free(data);
	return (0);
}













