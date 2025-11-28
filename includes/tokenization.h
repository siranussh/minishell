/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:40 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/28 22:25:28 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <aio.h>

# define REDIR_IN 1
# define REDIR_HEREDOC 2
# define REDIR_OUT 3
# define REDIR_APPEND 4

void	setup_signals(void);

typedef struct s_env t_env;

typedef struct s_env_exp
{
	char	**env;
	char	*path;
	int		num_env;
}	t_env_exp;

typedef struct s_flags
{
	int		pipe;
	int		quote;
	int		has_special;
}	t_flags;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**tokens;
	int				num_tokens;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	char			*delimiter;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;

	t_redir			*redirs;
	t_flags			*flags;
	t_env_exp		*env;
}	t_cmd;

typedef struct s_data
{
	int				total_chars;
	// int				heredoc;
	// int				fd_in;
	// int				fd_out;
	// int				nb_cmds;
	// char			*pipe;
	// char 			*pids;
	// char			*cmd_options;
	// char			*cmd_path;
	t_cmd			*cmd;
	t_flags			*flags;
	t_env_exp		*env_exp;
	t_env			*env;
}	t_data;

t_data	*init(void);
t_cmd	*init_cmd(t_data *data, char *line);
int		exit_error(char *str, int code);
void	print_error(char *name, char *file, char *err);
int		pipe_syntax_error(void);
int		quote_error(void);
int		redir_error(void);
int		export_error(char *arg);
void	unquote_all_tokens(t_cmd *cmd);
int		check_quotes_type(char *s);
int		find_closing_quote(int start, char *str, char c);
char	*skip_empty_quotes(char *str, t_cmd *cmd);
int		handle_quote_pair(char *str, char *res, int i, int *j);
int		is_empty_quotes_skippable(char *str, int i);
char	*delete_quotes(char *str, char c);
char	*str_tolower(char *str);
int		check_dquote(char *str, int is_double, int is_single,
			t_data *data);
char	*unqoute_str(char *str);
int		count_tokens(char *str);
int		parse_line(t_data **data, char *line,
			char ***tokens_by_pipe);
char	**split_cmds_by_pipe(char *str, char **result);
int		count_pipes(char *str);
int		check_pipe_seg(char *str);
char	**split_pipes(char *str);
t_cmd	*last_cmd(t_cmd **cmd);
int		count_tokens_array(char **tokens);
t_cmd	*build_cmd(t_data *data, char *line);
int		tokenize(t_data *data, t_cmd **cmd, char *read_line);
int		find_next_char(char *str, char c, int j);
int 	skip_quote_and_find(char *s, int *i, char quote);
char	redir_smb(int c);
int		is_redir(char **token);
int		redir_type(char *str);
int		is_other_op(char c);
int		find_next_redir(char *str);
int		check_redir(char **arg, int i);
char	**remove_token(char **tokens, int index);
char	**add_token(char **tokens, char *new, int j);
char	**split_redirection_start(char **tokens, int j, char c);
void	redir_tokens(t_cmd *cmd);
char	**split_redirection_tokens(char **tokens, int j, char c, int k);
char	**split_redirection_parts(char **tokens, int j, int i, int k);
void	replace_token_with_array(char ***tokens, int pos, char **arr, int arr_count);
void	normalize_redirections(t_cmd *cmd);
char	**split_redirs_token(char *tok, int *count);
int		check_redir_at(char *str, int i);
#endif
