/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:27:01 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/27 17:42:04 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	// execute single command
	// t_env *env = env_parse(envp);
	// char *cmd1[] = {"ll", NULL};
	// execute_single_command(cmd1, env);

	// execute pipeline
    t_env   *env;
    t_cmd1  *cmd1_ls;
    t_cmd1  *cmd1_wc;
    t_cmd1  *head;
    t_cmd   *cmd;
    t_pipe  *p;

    // 1. Parse environment
    env = env_parse(envp);

    // 2. Allocate first command: ls -l
    cmd1_ls = malloc(sizeof(t_cmd1));
    if (!cmd1_ls)
        return (1);
    memset(cmd1_ls, 0, sizeof(t_cmd1));
    cmd1_ls->cmd = ft_strdup("ls");
	cmd1_ls->tokens = malloc(sizeof(char *) * 3);
	if (!cmd1_ls->tokens)
		return (1);
    cmd1_ls->tokens[0] = ft_strdup("-l");
    cmd1_ls->tokens[1] = NULL;

    // 3. Allocate second command: wc -l
    cmd1_wc = malloc(sizeof(t_cmd1));
    if (!cmd1_wc)
        return (1);
    memset(cmd1_wc, 0, sizeof(t_cmd1));
    cmd1_wc->cmd = ft_strdup("wc");
	cmd1_wc->tokens = malloc(sizeof(char *) * 3);
	if (!cmd1_wc->tokens)
		return (1);
    cmd1_wc->tokens[0] = ft_strdup("-l");
    cmd1_wc->tokens[1] = NULL;

    // 4. Link commands
    cmd1_ls->next = cmd1_wc;
    cmd1_wc->next = NULL;
    head = cmd1_ls;

    // 5. Convert linked list (t_cmd1) to final command structure (t_cmd)
    cmd = store_cmds(head);

    // 6. Initialize pipe structure
    p = init_pipe_struct(cmd);

    // 7. Execute the pipeline
    execute_pipeline(cmd, env, p);

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
