/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:17 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/05 18:05:56 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*init(void)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_error("minishell: malloc failed", 1);
	data->env = NULL;
	data->flags = ft_calloc(1, sizeof(t_flags));
	if (!data->flags)
		exit_error("minishell: malloc failed", 1);
	data->p = ft_calloc(1, sizeof(t_pipe));
	if (!data->p)
		exit_error("minishell: malloc failed", 1);
	data->p->pids = NULL;
	data->flags->pipe = 0;
	data->flags->quote = 0;
	data->flags->has_special = 0;
	data->cmd = NULL;
	data->total_chars = 0;
	return (data);
}

void	unquote_all_tokens(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		if (cmd->tokens)
		{
			i = 0;
			while (cmd->tokens[i])
			{
				if (i > 0 && ft_strcmp(cmd->tokens[i - 1], "<<") == 0)
				{
					i++;
					continue;
				}
				tmp = unqoute_str(cmd->tokens[i]);
				free(cmd->tokens[i]);
				cmd->tokens[i] = tmp;
				i++;
			}
		}
		cmd = cmd->next;
	}
}

static t_data	*init_shell(char **envp)
{
	t_data	*data;
	t_env	*env;

	data = init();
	if (!data)
		exit_error("minishell: malloc failed", 1);
	env = env_parse(envp);
	data->env = env;
	data->env_exp = env_exp_from_list(env);
	if (!data->env_exp)
		exit_error("minishell: malloc failed", 1);

	return (data);
}

static int	process_line(t_data *data, char *line)
{
	if (!line)
		return 0;
	if (!tokenize(data, &data->cmd, line))
	{
		if (data->cmd)
		{
			free_cmd_list(data->cmd);
			data->cmd = NULL;
		}
		return (0);
	}
	if (data->cmd)
	{
		expand(&data->cmd, data);
		unquote_all_tokens(data->cmd);
	}
	return (1);
}

static void	exec_and_free(t_data *data, char *line)
{
	data->p = init_pipe_struct(data);
	data->p->exit_code = execute(data->cmd, data, data->p);
	if (data->p && data->p->pids)
	{
		free(data->p->pids);
		data->p->pids = NULL;
	}
	if (data->cmd)
	{
		free_cmd_list(data->cmd);
		data->cmd = NULL;
	}
	free(line);
}

static void	process_input_loop(t_data *data)
{
	char	*line;

	change_shlvl_value(data->env);
	while (1)
	{
		setup_signals();
		line = readline("minishell> ");
		if (!line)
			break ;
		if (check_spaces(line) == -1 || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!process_line(data, line))
			continue ;
		if (!data->cmd)
		{
			free(line);
			continue;
		}
		exec_and_free(data, line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = init_shell(envp);
	process_input_loop(data);
	free_data(data);
	// cleanup_shell(data);
	// rl_clear_history();
	// clear_history();  macOS version
	return (0);
}
