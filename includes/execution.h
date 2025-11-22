/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:04:35 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:57:10 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_pipe
{
	int		prev_fd;
	int		cmds_count;
	int		*pids;
	int		exit_code;
}	t_pipe;

// join_cmd_tokenc.c
char	**join_cmd_tokens(char *cmd, char **tokens, int num_tokens);

// cmd_list_utils.c
int		ft_cmd_size(t_cmd *cmds);

// init_struct.c
t_pipe	*init_pipe_struct(t_cmd *cmds);
t_redir	*init_redir(int type, char *filename);

// redir_utils.c
void	add_redir_back(t_redir **list, t_redir *new);
/////// void	build_redir_list(t_cmd *cmd);
char	**remove_tokens_from_array(char **tokens, int start, int count);

// heredoc.c
void	process_all_heredocs(t_cmd *cmds);

// execute_built_in.c
int		only_builtin(t_cmd *cmd, t_data *data);

// parse_redirs.c
void	parse_redirs(t_cmd *cmd);
void	setup_redirs(t_cmd *cmd);

// pipeline_utils.c
void	dup2_and_close(int fd1, int fd2);
int		wait_for_children(t_pipe *p);
char	**cpy_str_arr(char **str);

// find_cmd_path.c
char	*find_cmd_path(char *cmd, t_env *env);

// execute_single_cmd.c
int		args_count(char **args);
char	**env_to_array(t_env *env);
int		execute_single_command(char **args, t_data *data);

// execute_pipeline.c
void	setup_child_pipes_and_redirs(t_cmd *cmd, int prev_fd, int pipe_fd[2]);
int		child_process(t_cmd *cmd, t_pipe *p,  t_data *data, int pipe_fd[]);
void	execute_pipeline(t_cmd *cmds, t_data * data, t_pipe *p);

// execute.c
void	execute(t_cmd *cmds, t_data *data, t_pipe *p);

# endif
