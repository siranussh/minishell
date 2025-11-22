/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:04:35 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 21:39:35 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXECUTION_H
# define EXECUTION_H

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


/************** NEW EXECUTION **************/
// get_status.c
void	set_status(int status);
int		get_status(void);

// execute_built_in.c
void	parse_redirs_builtin(t_cmd *cmd);
void	setup_redirs_builtin(t_cmd *cmd);
void	process_all_heredocs(t_cmd *cmds);
int		only_builtin(t_cmd *cmd, t_data *data);

// redir_utils_new.c
void	parse_redirs_new(t_cmd *cmd);

// execute_pipeline.c
void		execute_pipeline(t_cmd *cmds, t_data * data, t_pipe *p);

// execute_new.c
void	execute_new(t_cmd *cmds, t_data *data, t_pipe *p);

/*******************************************/

// cmd_list_utils.c
int		ft_cmd_size(t_cmd *cmds);

// heredoc.c
void	get_heredoc(t_cmd *cmds);
void	handle_heredocs(t_cmd *cmds);

// init_struct.c
t_pipe	*init_pipe_struct(t_cmd *cmds);
t_redir	*init_redir(int type, char *filename);

// join_cmd_tokenc.c
char	**join_cmd_tokens(char *cmd, char **tokens, int num_tokens);

// pipeline_utils.c
void	dup2_and_close(int fd1, int fd2);
int		wait_for_children(t_pipe *p);
char	**cpy_str_arr(char **str);

// redir_utils.c
// int		get_redir_type(char *token);
void	add_redir_back(t_redir **list, t_redir *new);
void	setup_redirections(t_cmd *cmd);
void	parse_redirections(t_cmd *cmd);
void	build_redir_list(t_cmd *cmd);
char	**remove_tokens_from_array(char **tokens, int start, int count);

// setup_input_output.c
void	setup_input(t_cmd *curr, int prev_fd);
void	setup_output(t_cmd *curr, int pipe_fd[]);

// child_parent_prcs.c
void	child_process(t_cmd *curr, t_pipe *p, t_data *data, int pipe_fd[]);
void	parent_process(t_pipe *p, t_cmd *curr, int pid, int pipe_fd[]);

// execute_pipeline.c
void	execute_one_command(t_cmd *curr, t_pipe *p, t_data *data);
int		execute(t_cmd *cmds, t_data *data, t_pipe *p);

// find_cmd_path.c
char	*find_cmd_path(char *cmd, t_env *env);

// execute_single_cmd.c
int		args_count(char **args);
char	**env_to_array(t_env *env);
int		execute_single_command(char **args, t_data *data);

# endif
