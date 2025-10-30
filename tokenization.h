/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:40 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/27 20:03:34 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENAZIATION_H
#define TOKENAZIATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>


int g_exit_code;
void setup_signals(int parent_mode);

typedef struct s_env
{
    char **env;
    char *path;
    int num_env;
} t_env;

typedef struct s_flags
{
    int pipe;
    int quote;
    int	has_special;
} t_flags;

typedef struct s_cmd
{
    struct s_cmd *next;
    char *cmd;
    char **tokens;
    int num_tokens;
    t_flags	*flags;
    t_env *env;
} t_cmd;

typedef struct s_data
{
    int total_chars;
    t_cmd *cmd;
    t_env *env;
    t_flags *flags;
} t_data;

t_data *init(void);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
int	ft_isalpha(int c);
int	ft_isdigit(int n);
int	ft_isalnum(int c);
int	ft_tolower(int c);

int exit_error(char *str, int code);
void print_error(char *name, char *file, char *err);
int pipe_syntax_error(void);
int quote_error(void);
int redir_error(void);

int check_quotes_type(char *s);
int find_closing_quote(int start, char *str, char c);
char *skip_empty_quotes(char *str, t_cmd *cmd);
char *delete_quotes(char *str, char c);
char *str_tolower(char *str);
int check_dquote(char *str, int is_double, int is_single, t_data *data);
char *unqoute_str(char *str);
int count_tokens(char *str);
int parse_line(t_data **data, char *line, char ***tokens_by_pipe);
char **split_cmds_by_pipe(char *str, char **result);
int count_pipes(char *str);
int check_pipe_seg(char *str);
char **split_pipes(char *str);
t_cmd *last_cmd(t_cmd **cmd);
t_cmd *build_cmd(t_data *data, char *line);
int tokenize(t_data *data, t_cmd **cmd, char *read_line);

char redir_smb(int c);
int is_redir(char **token);
int redir_type(char *str);
int is_other_op(char c);
int find_next_redir(char *str);
int	check_redir(char **arg, int i);
char **remove_token(char **tokens, int index);
char **add_token(char **tokens, char *new, int j);
char **split_redirection_start(char **tokens, int j, char c);
char **split_redirection_tokens(char **tokens, int j, char c, int k);
void redir_tokens(t_cmd *cmd);

int find_next_char(char *str, char c, int j);
int	skip_quote_and_find(char *s, int *i, char c, int j);
int is_special(char c);
char *extract_value_name(char *line);
char *extract_after_special(char *line, int i, t_cmd *cmd);

char *extract_env_value(char *str);
char *expand_dollar(char *new_line, char *line, char *var, int c);
char *expand_line(char *line, char *var);
char *delete_invalid_dollar(char *str, int i, int j);
int	exp_strcmp(char *s1, char *s2);
char *cmp_value_name(t_cmd *cmd, char *line, char *name);
char *replace_val(t_cmd *cmd, char *line, char **rest_line);
char *replace_all_val(t_cmd *cmd, char *str, char *rest_line);
char *exp_strjoin(char *s1, char *s2, size_t i, size_t j);

int check_dollar_purpose(char *line);
int is_tilde_path(char *str);
char *replace_tilde(char *str);
int is_invalid_dollar(char *str);
int is_digit_or_special(int i);
char *replace_exit_code(char *str,int i);
char *replace_all_exit_code(char *str);
void expand(t_cmd **cmd);
int check_spaces(char *str);
#endif