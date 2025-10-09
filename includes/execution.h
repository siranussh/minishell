/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:30:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/10 00:18:45 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXECUTION_H
# define EXECUTION_H 

#include <sys/wait.h> // waitpid()

typedef struct	s_cmd
{
	char	**args;
	char	*path;
	int		input_fd;
	int		output_fd;
} t_cmd;

// find_cmd_path.c
char	*find_cmd_path(char *cmd, t_env *env);

// execute.c
int		args_count(char **args);
char	**env_to_array(t_env *env);
int		execute_single_command(char **args, t_env *env);


# endif