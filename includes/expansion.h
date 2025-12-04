/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:59:45 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/04 13:59:52 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef struct s_env		t_env;
typedef struct s_cmd		t_cmd;
typedef struct s_data		t_data;
typedef struct s_env_exp	t_env_exp;

// expand_dollar_handler.c
char	*collapse_dollars(char *s);
char	*get_env_var(t_env_exp *env, char *s, int i, int *len);
char	*expand_only_dollars(char *line, int pos, int dollar_count);
char	*expand_dollars_simple(char *line, int pos, t_env_exp *env);

// expand_exit_code.c
char	*replace_exit_code(char *str, int i);
char	*replace_all_exit_code(char *str);
int		is_var_char(char c);
int		get_var_len(char *s, int i);

// expand_libft_modifs.c
int		exp_strcmp(char *s1, char *s2);
char	*exp_strjoin(char *s1, char *s2, size_t i, size_t j);
int		count_dollars(char *line, int pos);

// expand_symb_utils.c
int		is_tilde_path(char *str);
char	*replace_tilde(char *str);
int		is_invalid_dollar(char *str);
int		is_digit_or_special(int i);
int		check_dollar_purpose(char *line);

// expand_utils.c
int		skip_quote_and_find(char *s, int *i, char quote);
int		find_next_char(char *s, char target, int j);
int		is_special(char c);
char	*cmp_value_name(char *line, char *name, t_env_exp *env);

// expand_var_utils.c
char	*extract_value_name(char *line);
char	*extract_after_special(char *line, int i, t_cmd *cmd);
char	*replace_val(t_cmd *cmd, char *line, char **rest_line,
			t_env_exp *env);
char	*replace_all_val(t_cmd *cmd, char *str, char *rest_line,
			t_env_exp *env);

// expand_var.c
int		handle_quotes(char c, int *in_single, int *in_double);
char	*handle_dollar(char *str, int *i, t_env_exp *env);
char	*expand_exit_status(char *str, int *i);
char	*replace_with_value(char *str, int *i, char *val, int skip_len);
char	*build_new_line(char *line, char *insert, int pos, int remove_len);

// expand.c
char	*extract_env_value(char *str);
char	*expand_dollar(char *new_line, char *line, char *var,
			int c);
char	*expand_line(char *line, char *var);
char	*delete_invalid_dollar(char *str, int i, int j);
void	expand(t_cmd **cmd, t_data *data);

#endif
