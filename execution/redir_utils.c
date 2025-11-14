/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:49:17 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/14 22:12:58 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

// int	get_redir_type(char *token)
// {
// 	if (!token)
// 		return (-1);
// 	if (ft_strcmp(token, "<") == 0)
// 		return (1);
// 	else if (ft_strcmp(token, "<<") == 0)
// 		return (2);
// 	else if (ft_strcmp(token, ">") == 0)
// 		return (3);
// 	else if (ft_strcmp(token, ">>") == 0)
// 		return (4);
// 	return (-1);
// }

void	add_redir_back(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	setup_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	// if (cmd->fd_in > 0)
	// {
	// 	dup2(cmd->fd_in, STDIN_FILENO);
	// 	close(cmd->fd_in);
	// 	cmd->fd_in = -1;
	// }
	r = cmd->redirs;
	while (r)
	{
		if (r->type == 1)
		{
	
			fd = open(r->filename, O_RDONLY);
			if (fd < 0)
				perror(r->filename);
			else
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		else if (r->type == 2)
		{
			if (cmd->fd_in != -1)
			{
				dup2(cmd->fd_in, STDIN_FILENO);
				close(cmd->fd_in);
			}
		}
		else if (r->type == 3)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				perror(r->filename);
			else
			{
				dup2(fd, STDOUT_FILENO);
				close (fd);
			}
		}
		else if (r->type == 4)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				perror(r->filename);
			else
			{	
				dup2(fd, STDOUT_FILENO);
				close (fd);
			}
		}
		r = r->next;
	}
}

void	parse_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->tokens)
		return ;
	while (cmd->tokens[i])
	{
		if (strcmp(cmd->tokens[i], "<") == 0 && cmd->tokens[i + 1])
		{
			free(cmd->infile);
			cmd->infile = ft_strdup(cmd->tokens[i + 1]);
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue;
		}
		else if (strcmp(cmd->tokens[i], "<<") == 0 && cmd->tokens[i + 1])
		{
			cmd->heredoc = 1;
			free(cmd->delimiter);
			cmd->delimiter = ft_strdup(cmd->tokens[i + 1]);
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
		}
		else if (strcmp(cmd->tokens[i], ">") == 0 && cmd->tokens[i + 1])
		{
			free(cmd->outfile);
			cmd->outfile = ft_strdup(cmd->tokens[i + 1]);
			cmd->append = 1;
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">>") == 0 && cmd->tokens[i + 1])
		{
			free(cmd->outfile);
			cmd->outfile = ft_strdup(cmd->tokens[i + 1]);
			cmd->append = 2;
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		i++;
	}
}

void	build_redir_list(t_cmd *cmd)
{
	if (cmd->infile)
		add_redir_back(&cmd->redirs, init_redir(1, cmd->infile));
	if (cmd->heredoc && cmd->delimiter)
		add_redir_back(&cmd->redirs, init_redir(2, cmd->delimiter));
	if (cmd->outfile)
	{
		if (cmd->append == 2)
			add_redir_back(&cmd->redirs, init_redir(4, cmd->outfile));
		else
			add_redir_back(&cmd->redirs, init_redir(3, cmd->outfile));
	}
}

char	**remove_tokens_from_array(char **tokens, int start, int count)
{
	int		i;
	int		j;
	int		old_len;
	int		new_len;
	char	**new_tokens;

	i = 0;
	j = 0;
	old_len = 0;
	if (!tokens)
		return (NULL);
	while (tokens[old_len])
		old_len++;
	new_len = old_len - count;
	if (new_len <= 0)
	{
		new_tokens = malloc(sizeof(char *));
		new_tokens[0] = NULL;
		return (new_tokens);
	}
	new_tokens = malloc(sizeof(char *) * (new_len + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (i < old_len)
	{
		if (i >= start && i < start + count)
		{
			free(tokens[i]);
			i++;
			continue;
		}
		new_tokens[j++] = tokens[i++];
	}
	new_tokens[j] = NULL;
	free(tokens);
	return (new_tokens);
}
