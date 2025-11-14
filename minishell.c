/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:17 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/13 16:15:07 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_data *init(void)
{
    t_data *data = ft_calloc(1, sizeof(t_data));
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
    return data;
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


int main(int argc, char **argv, char **envp)
{
    t_data  *data;
    t_env   *env;
    t_pipe  *p;
    char    *line;

    (void)argc;
    (void)argv;
    p = NULL;
    data = init();
    if (!data)
        exit_error("minishell: malloc failed", 1);
    env = env_parse(envp);
    data->env = env;
    data->env_exp = env_exp_from_list(env);
    if (!data->env_exp)
        exit_error("minishell: malloc failed", 1);
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
            free(line);
            continue ;
        }
        if (data->cmd)
        {
            redir_tokens(data->cmd);
            expand(&data->cmd, data);
            unquote_all_tokens(data->cmd);
        }
        p = init_pipe_struct(data->cmd);
        execute_pipeline(data->cmd, data, p);
        free(line);
    }
    free(data->cmd);
    free_env_list(data->env);
    if (data->env_exp)
    free_env_exp(&data->env_exp);
    return (0);
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
