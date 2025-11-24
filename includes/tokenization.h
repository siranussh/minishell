/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:40 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/24 16:57:24 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <aio.h>

# define REDIR_IN 1
# define REDIR_HEREDOC 2
# define REDIR_OUT 3
# define REDIR_APPEND 4

void	setup_signals(int parent_mode);

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
	int				type;//1 < 2 << 3 > 4 >>
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**tokens;
	int				num_tokens;
	char			*infile;// <
	char			*outfile;// > >>
	int				append;// 1 if > 2 if >>
	int				heredoc;// <<
	char			*delimiter;
	int				fd_in;
	int				fd_out;
	// int				pid;
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

int		exit_error(char *str, int code);
void	print_error(char *name, char *file, char *err);
int		pipe_syntax_error(void);
int		quote_error(void);
int		redir_error(void);
int		export_error(char *arg);
void	disable_ctrl_echo(void);
void	enable_ctrl_echo(void);
void	unquote_all_tokens(t_cmd *cmd);
int		check_quotes_type(char *s);
int		find_closing_quote(int start, char *str, char c);
char	*skip_empty_quotes(char *str, t_cmd *cmd);
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
t_cmd	*build_cmd(t_data *data, char *line);
int		tokenize(t_data *data, t_cmd **cmd, char *read_line);

int		find_next_char(char *str, char c, int j);
int		skip_quote_and_find(char *s, int *i, char c, int j);
int		is_special(char c);
char	*extract_value_name(char *line);
char	*extract_after_special(char *line, int i, t_cmd *cmd);
char	*extract_env_value(char *str);
char	*expand_dollar(char *new_line, char *line, char *var,
			int c);
char	*expand_line(char *line, char *var);
char	*delete_invalid_dollar(char *str, int i, int j);
int		exp_strcmp(char *s1, char *s2);
char	*cmp_value_name(char *line, char *name, t_env_exp *env);
char	*replace_val(t_cmd *cmd, char *line, char **rest_line, t_env_exp *env);
char	*replace_all_val(t_cmd *cmd, char *str, char *rest_line, t_env_exp *env);
char	*exp_strjoin(char *s1, char *s2, size_t i, size_t j);
int		check_dollar_purpose(char *line);
int		is_tilde_path(char *str);
char	*replace_tilde(char *str);
int		is_invalid_dollar(char *str);
int		is_digit_or_special(int i);
char	*replace_exit_code(char *str, int i);
char	*replace_all_exit_code(char *str);
void	expand(t_cmd **cmd, t_data *data);
int		check_spaces(char *str);
int		skip_spaces(char *str, int i);
t_env_exp	*env_exp_from_list(t_env *env_list);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
void	refresh_env_exp(t_data *data);
int		built_in_export_wrapper(char **args, int argc, t_data *data);
char	*expand_var(t_data *data, char *key);
void	free_env_exp(t_env_exp **env_exp_ptr);
int		built_in_unset_wrapper(char **args, t_data *data);

int	has_only_dollars_or_dollars_before_var(char *s);
char *collapse_dollars(char *s);
int is_var_char(char c);
int get_var_len(char *s, int i);
char *get_env_var(t_env_exp *env, char *s, int i, int *len);
int count_dollars(char *line, int pos);
char	*expand_only_dollars(char *line, int pos, int dollar_count);
char	*expand_dollars_simple(char *line, int pos, t_env_exp *env);
char	*make_prefix(int prefix_len);
char	*build_insert(char *line, int pos, int dollar_count, int var_len, t_env_exp *env);
char	*build_new_line(char *line, char *insert, int pos, int remove_len);
char	*expand_var_with_prefix(char *line, int pos, int dollar_count, int var_len, t_env_exp *env);
char **split_var_value(char *str);
char **expand_var_for_execution(char *expanded_value);

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
#endif
