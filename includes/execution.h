/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:30:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/12 00:25:17 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXECUTION_H
# define EXECUTION_H 

#include <sys/wait.h> // waitpid()
//
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_cmd
{
	char		**cmds;
	char		*infile;// <
	char		*outfile;// > >>
	int			append;
	int			heredoc;
	char		*delimiter;
	int			fd_in;
	int			fd_out;
	struct scmd	*next;
}	t_cmd;

/******************************/
// typedef struct s_data
// {
// 	char	**av;
// 	int		ac;
// 	int		heredoc;
// 	int		fd_in;
// 	int		fd_out;
// 	int		*pipe;
// 	int		nb_cmds;
// 	int		child;
// 	int		*pids;
// 	char	**cmd_options;
// 	char	*cmd_path;
// }		t_data;
/**************************** */

// find_cmd_path.c
char	*find_cmd_path(char *cmd, t_env *env);

// execute.c
int		args_count(char **args);
char	**env_to_array(t_env *env);
int		execute_single_command(char **args, t_env *env);

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