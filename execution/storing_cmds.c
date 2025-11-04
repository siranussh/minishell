/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:10:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/03 23:21:29 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

t_cmd	*store_cmds(char **tokens)
{
	int		i;
	char	**split;
	t_cmd	*head;
	t_cmd	*tmp;

	i = 1;
	head = NULL;
	tmp = NULL;
	while (tokens[i])
	{
		split = ft_split(tokens[i], ' ');
		// split = join_cmd_tokens(cmd1);
		tmp = ft_cmd_new(split);
		ft_cmd_add_back(&head, tmp);
		ft_free(split);
		i++;
	}
	return (head);
}

static void	handle_heredoc(t_cmd *cmds, int *i)
{
	(*i)++;
	cmds->heredoc = 1;
	cmds->delimiter = ft_strdup(cmds->tokens[*i]);
}

static void	handle_output_redir(t_cmd *cmds, int *i, int n)
{
	(*i)++;
	cmds->append = n;
	cmds->outfile = ft_strdup(cmds->tokens[*i]);
}

void	check_cmds(t_cmd *cmds)
{
	int	i;
	int	n;

	while (cmds)
	{
		i = 0;
		while (cmds->tokens[i])
		{
			n = is_heredoc_redir_present(cmds->tokens[i]);
			if (n == 1)// <<
				handle_heredoc(cmds, &i);
			else if (n == 2)// <
			{
				i++;
				cmds->infile = ft_strdup(cmds->tokens[i]);
			}
			else if (n == 3)// >
				handle_output_redir(cmds, &i, 1);
			else if (n == 4)// >>
				handle_output_redir(cmds, &i, 2);
			i++;
		}
		cmds = cmds->next;
	}
}

// For pipeline I'll receive char ** with cmd segments
// echo hi | grep h | wc -l
//
// result[0] = "echo hi << in";
// result[1] = " grep h ";
// result[2] = " wc -l";
// result[3] = NULL;
