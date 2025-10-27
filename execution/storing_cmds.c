/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:10:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/27 17:10:05 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

t_cmd	*store_cmds(t_cmd1 *cmd1)
{
	int		i;
	char	**split;
	t_cmd	*head;
	t_cmd	*tmp;

	i = 0;
	while (cmd1)
	{
		// split = ft_split(args[i], ' ');
		split = join_cmd_tokens(cmd1);
		tmp = ft_cmd_new(split);
		ft_cmd_add_back(&head, tmp);
		ft_free(split);
		cmd1 = cmd1->next;
	}
	return (head);
}

static void	handle_heredoc(t_cmd *cmds, int *i)
{
	(*i)++;
	cmds->heredoc = 1;
	cmds->delimiter = ft_strdup(cmds->cmd_line[*i]);
}

static void	handle_output_redir(t_cmd *cmds, int *i, int n)
{
	(*i)++;
	cmds->append = n;
	cmds->outfile = ft_strdup(cmds->cmd_line[*i]);
}

void	check_cmds(t_cmd *cmds)
{
	int	i;
	int	n;

	while (cmds)
	{
		i = 0;
		while (cmds->cmd_line[i])
		{
			n = is_heredoc_redir_present(cmds->cmd_line[i]);
			if (n == 1)// <<
				handle_heredoc(cmds, &i);
			else if (n == 2)// <
			{
				i++;
				cmds->infile = ft_strdup(cmds->cmd_line[i]);
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
