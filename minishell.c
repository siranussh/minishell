/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:17 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/28 22:52:12 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

// static void create_env_exp(t_env_exp *env_exp, char **ev)
// {
//     int i = 0;

//     while (ev[i])
//         i++;
//     env_exp->num_env = i;
//     env_exp->env = ft_calloc(i + 1, sizeof(char *));
//     if (!env_exp->env)
//         exit_error("minishell: malloc failed", 1);
//     env_exp->path = NULL;
//     while (--i >= 0)
//     {
//         env_exp->env[i] = ft_strdup(ev[i]);
//         if (!env_exp->path && ft_strncmp(ev[i], "PATH=", 5) == 0 && ft_strlen(ev[i]) > 5)
//             env_exp->path = ft_substr(ev[i], 5, ft_strlen(ev[i]) - 5);
//         if (ft_strncmp(ev[i], "SHLVL=", 6) == 0)
//         {
//             free(env_exp->env[i]);
//             env_exp->env[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(ev[i] + 6) + 1));
//         }
//     }
//     env_exp->env[env_exp->num_env] = NULL;

//     if (!env_exp->path)
//         env_exp->path = ft_strdup("./");
// }

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
	data->flags->pipe = 0;
	data->flags->quote = 0;
	data->flags->has_special = 0;
	data->cmd = NULL;
	data->total_chars = 0;
	return (data);
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

//before cut 28.11.25
// int main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;
// 	t_env	*env;
// 	t_pipe	*p;
// 	char	*line;
// 	char *processed_line;

// 	(void)argc;
// 	(void)argv;
// 	p = NULL;
// 	data = init();
// 	if (!data)
// 		exit_error("minishell: malloc failed", 1);
// 	env = env_parse(envp);
// 	data->env = env;
// 	data->env_exp = env_exp_from_list(env);
// 	if (!data->env_exp)
// 		exit_error("minishell: malloc failed", 1);
// 	while (1)
// 	{
// 		setup_signals();
// 		line = readline("minishell> ");
// 		if (!line)
// 			break ;
// 		if (check_spaces(line) == -1 || line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		processed_line = skip_empty_quotes(line, data->cmd);
// 		if (!tokenize(data, &data->cmd, line))
// 		{
// 			free(processed_line); 
// 			// free(line); // double free er talis
// 			continue ;
// 		}
// 		free(processed_line);
// 		if (data->cmd)
// 		{
// 			// redir_tokens(data->cmd);
// 			expand(&data->cmd, data);
// 			unquote_all_tokens(data->cmd);
// 		}
// 		p = init_pipe_struct(data->cmd);
// 		execute(data->cmd, data, p);////new execution////
// 		free(line);
// 	}
// 	free(p);
// 	free(data->cmd);
// 	free_env_list(data->env);
// 	if (data->env_exp)
// 		free_env_exp(&data->env_exp);
// 	return (0);
// }

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

static void	cleanup_shell(t_data *data)
{
	free(data->cmd);
	free_env_list(data->env);
	if (data->env_exp)
		free_env_exp(&data->env_exp);
}

static char	*read_shell_line(void)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
		return (NULL);
	if (check_spaces(line) == -1 || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}

static int	process_line(t_data *data, char *line)
{
	char	*processed_line;

	processed_line = skip_empty_quotes(line, data->cmd);
	if (!tokenize(data, &data->cmd, line))
	{
		free(processed_line);
		return (0);
	}
	free(processed_line);

	if (data->cmd)
	{
		expand(&data->cmd, data);
		unquote_all_tokens(data->cmd);
	}
	return (1);
}

static void	exec_and_free(t_data *data, char *line)
{
	t_pipe	*p;

	p = init_pipe_struct(data->cmd);
	execute(data->cmd, data, p);
	free(p);
	free(line);
}

static void	process_input_loop(t_data *data)
{
	char	*line;

	change_shlvl_value(data->env);
	while (1)
	{
		setup_signals();
		line = read_shell_line();
		if (!line)
			break ;
		if (!process_line(data, line))
			continue ;
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
	cleanup_shell(data);
	// rl_clear_history();    
	// clear_history();  macOS version
	return (0);
}
