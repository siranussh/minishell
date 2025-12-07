/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:17 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/07 15:34:18 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
					continue ;
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

static int	process_line(t_data *data, char *line)
{
	if (!line)
		return (0);
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
	data->exit_code = execute(data->cmd, data, data->p);
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
		check_interactive_sigint(data);
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
			continue ;
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
	rl_clear_history();
	return (0);
}
