/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:38:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/15 23:06:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXECUTION_H
# define EXECUTION_H

#include <sys/wait.h> // waitpid()
# include <fcntl.h>
# include <readline/readline.h>
//
# include <string.h>
# include <errno.h>

typedef struct s_cmd
{
	char		**cmd_line;
	char		*infile;// <
	char		*outfile;// > >>
	int			append;// 1 if > 2 if >>
	int			heredoc;// <<
	char		*delimiter;
	int			fd_in;
	int			fd_out;
	struct s_cmd	*next;
}	t_cmd;


typedef struct s_pipe
{
	// char	**av;
	// int		ac;
	// int		heredoc;
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	int		nb_cmds;
	int		child;
	int		*pids;
	// char	**cmd_options;
	// char	*cmd_path;
}	t_pipe;


// cmd_list_utils.c
t_cmd	*ft_cmd_new(char **args);
void	ft_env_add_back(t_cmd **lst, t_cmd *new);
int		ft_cmd_size(t_cmd *cmds);

// pipeline_utils.c
int		is_heredoc_redir_present(char *str);
char	**cpy_str_arr(char **str);

// heredoc.c
void	get_heredoc(t_cmd *cmds);

// execute_pipeline.c

// storing_cmds.c
t_cmd	*store_cmds(char **args);
void	check_cmds(t_cmd *cmds);

// find_cmd_path.c
char	*find_cmd_path(char *cmd, t_env *env);

// execute_single_cmd.c
int		args_count(char **args);
char	**env_to_array(t_env *env);
int		execute_single_command(char **args, t_env *env);

// execute.c




/********************************************************/
// pipexxxxxxxx
void	free_str_or_arr_bonus(char *str, char **strs);
void	get_input_file_bonus(t_data *d);
void	get_output_file_bonus(t_data *d);
void	get_heredoc(t_data *d);
char	*get_cmd_bonus(char *cmd, t_data *data);
t_data	init_bonus(int ac, char **av, char **envp);
void	error_bonus(int error_status, t_data *data);
int		error_msg_bonus(char *str1, char *str2, char *str3, int erno);
void	close_fds_bonus(t_data *data);
int	pipex_main(int ac, char **av, char **envp);

# endif
