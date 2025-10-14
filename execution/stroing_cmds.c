/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stroing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:15:38 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/13 13:15:38 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

t_cmd	*store_cmds(char **args)
{
	int		i;
	char	**split;
	t_cmd	*head;
	t_cmd	*tmp;

	if (!args || !*args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		split = ft_split(args[i], ' ');
		tmp = ft_cmd_new(split);
		ft_cmd_add_back(&head, tmp);
		ft_free(split);
		i++;
	}
	return (head);
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
			if (n = 1)// <<
			{
				cmds->heredoc = 1;
				i++;
				cmds->delimiter = ft_strdup(cmds->cmd_line[i]);
			}
			else if (n = 2)// <
			{
				i++;
				cmds->infile = ft_strdup(cmds->cmd_line[i]);
			}
			else if (n = 3)// >
			{
				i++;
				cmds->append = 1;
				cmds->outfile = ft_strdup(cmds->cmd_line[i]);
			}
			else if (n = 4)// >>
			{
				i++;
				cmds->append = 2;
				cmds->outfile = ft_strdup(cmds->cmd_line[i]);
			}
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
