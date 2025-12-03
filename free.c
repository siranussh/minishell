/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:46 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/03 23:21:09 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char **str)
{
	int	i;

	// if (!str || !*str)
	// 	return ;
	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->tokens)
		ft_free(cmd->tokens);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->delimiter)
		free(cmd->delimiter);
	if (cmd->redirs)
		free_redirs(cmd->redirs);
	// if (cmd->flags)
	// 	free(cmd->flags);
	// if (cmd->env)
	// {
	// 	if (cmd->env->env)
	// 		ft_free(cmd->env->env);
	// 	if (cmd->env->path)
	// 		free(cmd->env->path);
	// 	free(cmd->env);
	// }
	free(cmd);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_cmd(cmd);
		cmd = tmp;
	}
}

void	free_flags(t_flags *flags)
{
	if (!flags)
		return ;
	free(flags);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd)
		free_cmd_list(data->cmd);
	if (data->flags)
		free_flags(data->flags);
	if (data->p)
		free_pipe_struct(data->p);
	if (data->env)
		free_env_list(data->env);
	if (data->env_exp)
		free_env_exp(&data->env_exp);
	free(data);
}

void	free_pipe_struct(t_pipe *p)
{
	if (p)
	{
		if (p->pids)
			free(p->pids);
		free(p);
	}
}
