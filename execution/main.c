/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:26:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/12 00:21:02 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	main(int argc, char **argv, char **envp)
{
	// t_env	*env;

	(void)argc;
	(void)argv;
	// (void)envp;
	// char *str_echo[] = {"echo", "-n", "-nn", "barev", "aziz", "-n", "jan", NULL};
	// char *str_env[] = {"env", NULL};
	// char *str[] = {"export", "zibil=foo", "ANfgh+=asd", NULL};
	// char *str1[] = {"export", "zibil=bar", NULL};
	// char *str_unset[] = {"unset", "_", NULL};
	// char *str_exit[] = {"exit", "42", NULL};
	
	// built_in_exit(2, str_exit);
	// built_in_echo(str_echo);
	// env = env_parse(envp);
	// built_in_env(1, str_env, env);
	// printf("\n--------------------------------------------------------\n");

	// built_in_export(str, 3, &env);
	// printf("\n--------------------------------------------------------\n");
	// built_in_env(1, str_env, env);
	// printf("\n\n\n");
	// built_in_export(str, 1, &env);
	// printf("\n\n\n");

	// built_in_export(str1, 2, &env);
	// built_in_export(str, 1, &env);
	// printf("\n\n\n");
	// built_in_unset(str_unset, &env);
	// built_in_env(1, str_env, env);

	t_env *env = env_parse(envp);
	char *cmd1[] = {"ls", "-l", NULL};
	execute_single_command(cmd1, env);
	
	// while (1)
	// {
    // 	line = readline("minishell> ");
    // 	//cmds = parse_line(line);
    // 	execute(cmds, env);
    // 	free_all(cmds);
	// }
	// free_env_list(env);
	
	return (0);
}
