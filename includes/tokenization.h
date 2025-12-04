/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:40 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/04 23:33:44 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <aio.h>

# define REDIR_IN 1
# define REDIR_HEREDOC 2
# define REDIR_OUT 3
# define REDIR_APPEND 4

typedef struct s_env	t_env;
typedef struct s_pipe	t_pipe;

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
	int				quoted_delimiter;
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
	int			total_chars;
	t_pipe		*p;
	t_cmd		*cmd;
	t_flags		*flags;
	t_env_exp	*env_exp;
	t_env		*env;
}	t_data;

// 	create_token.c
t_cmd	*init_cmd(t_data *data, char *line);
t_cmd	*build_cmd(t_data *data, char *line);

// handle_quotes.c
int		check_quotes_type(char *s);
int		check_dquote(char *str, int is_double, int is_single,
			t_data *data);
int		handle_quote_pair(char *str, char *res, int i, int *j);

// handle_quotes_2.c
int		is_empty_quotes_skippable(char *str, int i);
char	*skip_empty_quotes(char *str, t_cmd *cmd);

// token_pipe_utils.c
int		count_pipes(char *str);
char	**split_cmds_by_pipe(char *str, char **result);
int		check_pipe_seg(char *str);
char	**split_pipes(char *str);

// token_redir_utils.c
int		is_other_op(char c);
int		redir_type(char *str);
int		is_redir(char **token);
char	redir_smb(int c);
int		find_next_redir(char *str);
// token_redir.c
char	**remove_token(char **tokens, int index);
char	**add_token(char **tokens, char *new, int j);
char	**split_redirection_start(char **tokens, int j, char c);
char	**split_redirection_tokens(char **tokens, int j, char c, int k);
char	**split_redirection_parts(char **tokens, int j, int i, int k);

// token_redir2.c
void	redir_tokens(t_cmd *cmd);
char	**split_redirs_token(char *tok, int *count);

// token_redir3.c
int		check_redir_at(char *str, int i);
void	replace_token_with_array(char ***tokens, int pos, char **arr,
			int arr_count);
void	normalize_redirections(t_cmd *cmd);

// token_utils.c
int		count_tokens(char *str);
int		check_redir(char **tk, int i);
int		parse_line(t_data **data, char *line, char ***tokens_by_pipe);
t_cmd	*last_cmd(t_cmd **cmd);
int		count_tokens_array(char **tokens);

// token_utils_2.c
char	*delete_quotes(char *str, char c);

//tokenize.c
int		is_heredoc(char *tok);
int		token_is_heredoc_delimiter(char **tokens, int i);
int		tokenize(t_data *data, t_cmd **cmd, char *read_line);
int		check_invalid_redirections(t_cmd *cmd);

int		find_closing_quote(int start, char *str, char c);
int		find_next_char(char *str, char c, int j);

#endif
