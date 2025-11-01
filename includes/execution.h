/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:04:35 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/01 12:04:35 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// typedef struct s_cmd
// {
// 	char			**cmd_line;
// 	char			*infile;// <
// 	char			*outfile;// > >>
// 	int				append;// 1 if > 2 if >>
// 	int				heredoc;// <<
// 	char			*delimiter;
// 	int				fd_in;
// 	int				fd_out;
// 	int				cmd_index;
// 	int				pid;
// 	struct s_cmd	*next;
// }	t_cmd;

// typedef struct s_cmd1
// {
// 	struct s_cmd1	*next;
// 	char			*cmd;
// 	char			**tokens;
// 	int				num_tokens;
// }	t_cmd1;

typedef struct s_pipe
{
	int		index;
	int		fd_in;
	int		fd_out;
	int		prev_fd;
	int		cmds_count;
	int		child;
	int		*pids;
	int		exit_code;
	char	**env_arr;
}	t_pipe;

// cmd_list_utils.c
t_cmd	*ft_cmd_new(char **args);
void	ft_cmd_add_back(t_cmd **lst, t_cmd *new);
int		ft_cmd_size(t_cmd *cmds);

// heredoc.c
void	get_heredoc(t_cmd *cmds);

// init_struct.c
t_pipe	*init_pipe_struct(t_cmd *cmds);

// join_cmd_tokenc.c
char	**join_cmd_tokens(char *cmd, char **tokens, int num_tokens);

// pipeline_utils.c
void	dup2_and_close(int fd1, int fd2);
void	handle_heredocs(t_cmd *cmds);
int		wait_for_children(t_pipe *p);
int		is_heredoc_redir_present(char *str);
char	**cpy_str_arr(char **str);

// setup_input_output.c
void	setup_input(t_cmd *curr, int prev_fd);
void	setup_output(t_cmd *curr, int pipe_fd[]);

// child_parent_prcs.c
void	child_process(t_cmd *curr, t_pipe *p, t_env *env, int pipe_fd[]);
void	parent_process(t_pipe *p, t_cmd *curr, int pid, int pipe_fd[]);

// execute_pipeline.c
void	execute_one_command(t_cmd *curr, t_pipe *p, t_env *env);
int		execute_pipeline(t_cmd *cmds, t_env *env, t_pipe *p);

// storing_cmds.c
t_cmd	*store_cmds(char **tokens);
void	check_cmds(t_cmd *cmds);

// find_cmd_path.c
char	*find_cmd_path(char *cmd, t_env *env);

// redir_utils.c
char	*return_infile_redir(char **args, char *redir);

// execute_single_cmd.c
int		args_count(char **args);
char	**env_to_array(t_env *env);
int		execute_single_command(char **args, t_env *env);

// execute.c

# endif
