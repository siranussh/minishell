/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:00:43 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 15:00:43 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_redirs(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0
			|| ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}

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

static void	cpy_new_tokens(char **tokens, char **new_tokens,
		int start, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (i >= start && i < start + count)
		{
			free(tokens[i]);
			i++;
			continue ;
		}
		new_tokens[j++] = tokens[i++];
	}
	new_tokens[j] = NULL;
}

char	**remove_tokens_from_array(char **tokens, int start, int count)
{
	int		old_len;
	int		new_len;
	char	**new_tokens;

	if (!tokens)
		return (NULL);
	old_len = args_count(tokens);
	new_len = old_len - count;
	if (new_len <= 0)
	{
		new_tokens = malloc(sizeof(char *));
		new_tokens[0] = NULL;
		ft_free(tokens);
		return (new_tokens);
	}
	new_tokens = malloc(sizeof(char *) * (new_len + 1));
	if (!new_tokens)
		return (NULL);
	cpy_new_tokens(tokens, new_tokens, start, count);
	free(tokens);
	return (new_tokens);
}
