#ifndef EXPANSION_H
#define EXPANSION_H

typedef struct s_env t_env;
typedef struct s_cmd t_cmd;
typedef struct s_data t_data;
typedef struct s_env_exp t_env_exp;

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
int	handle_quotes(char c, int *in_single, int *in_double);
char	*handle_dollar(char *str, int *i, t_env_exp *env);
char	*expand_exit_status(char *str, int *i);
char	*replace_with_value(char *str, int *i, char *val, int skip_len);

#endif 