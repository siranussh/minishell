/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:17 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/02 14:46:39 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

t_data	*init(void)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		exit_error("minishell: malloc failed", 1);
	data->flags = ft_calloc(sizeof(t_flags), 1);
	if (!data->flags)
		exit_error("minishell: malloc failed", 1);
	return (data);
	data->flags->pipe = 0;
	data->flags->quote = 0;
	data->flags->has_special = 0;
	data->cmd = NULL;
	data->total_chars = 0;
}

// static void	print_tokens(t_cmd *cmd)
// {
// 	int		i;
// 	char	*unquoted;
// 	while (cmd)
// 	{
// 		if (cmd->cmd)
//     printf("Command: %s\n", cmd->cmd);
// 		if (cmd->tokens)
// 		{
// 			i = 0;
// 			while (cmd->tokens[i])
// 			{
// 				unquoted = unqoute_str(cmd->tokens[i]);
// 				free(cmd->tokens[i]);
// 				cmd->tokens[i] = unquoted;
// 				printf("  token[%d]: %s\n", i, cmd->tokens[i]);
// 				i++;
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// }

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
				tmp = unqoute_str(cmd->tokens[i]); // remove quotes from this token
				free(cmd->tokens[i]);              // free old token
				cmd->tokens[i] = tmp;              // replace with unquoted token
				i++;
			}
		}
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_env	*env;
	t_pipe	*p;
	char	*line;

	(void)argc;
	(void)argv;
	p = NULL;
	data = init();
	env = env_parse(envp);
	disable_ctrl_echo();
	setup_signals(1);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (check_spaces(line) == -1 || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!tokenize(data, &data->cmd, line))
		{
			printf("Tokenization failed.\n");
			continue ;
		}
		if (data->cmd)
		{
			redir_tokens(data->cmd);
			expand(&data->cmd);
			unquote_all_tokens(data->cmd);
		}
		p = init_pipe_struct(data->cmd);
		execute_pipeline(data->cmd, env, p);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;
// 	char	*line;

// 	(void)argc;
// 	(void)argv;
// 	data = init();
// 	data->env->env = envp;
// 	data->env->num_env = 0;
// 	while (envp[data->env->num_env])
// 		data->env->num_env++;
// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line)
// 			break ;
// 		if (check_spaces(line) == -1 || line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		data->flags->pipe = 0;
// 		data->flags->quote = 0;
// 		data->flags->has_special = 0;
// 		if (!tokenize(data, &data->cmd, line))
// 		{
// 			printf("Tokenization failed.\n");
// 			continue ;
// 		}
// 		if (data->cmd)
// 		{
// 			redir_tokens(data->cmd);
// 			expand(&data->cmd);
// 		}

// 		if (data->cmd)
// 			print_tokens(data->cmd);
// 		data->cmd = NULL;
// 	}
// 	g_exit_code = 0;
// 	free(data->flags);
// 	free(data);
// 	return (0);
// }
