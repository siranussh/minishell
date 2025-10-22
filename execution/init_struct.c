#include "../includes/builtins.h"
#include "../includes/execution.h"

t_pipe	*init_pipe_struct(t_cmd *cmds)
{
	t_pipe	*p;

	p = (t_pipe *)malloc(sizeof(t_pipe));
	if (!p)
		return (NULL);
	p->fd_in = -1;
	p->fd_out = -1;
	p->index = 0;
	p->prev_fd = -1;
	p->exit_code = 0;
	p->cmds_count = ft_cmd_size(cmds);
	if (p->cmds_count <= 0)
		return (free(p), NULL);
	p->pids = (int *)malloc(sizeof(int) * p->cmds_count);
	if (!p->pids)
	{
		free(p);
		return (NULL);
	}
	return (p);
}
