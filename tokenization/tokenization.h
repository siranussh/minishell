#ifndef TOKENAZIATION_H
#define TOKENAZIATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int global_error;

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

int exit_error(char *str, int code);
void print_error(char *name, char *file, char *err);
int pipe_syntax_error(void);
int quote_error(void);
int redir_error(void);

int check_quotes_type(char *str);
int find_closing_quote(int i, char *str, char c);
char *skip_empty_quotes(char *str, t_cmd *cmd);
char *delete_quotes(char *str, char c);
int check_dquote(char *str, int is_double, int is_single, t_data *data);
int count_tokens(char *str);
int parse_line(t_data **data, char *line, char ***tokens_by_pipe);
char **split_cmds_by_pipe(char *str, char **result);
int count_pipes(char *str);
int check_pipe_seg(char *str);
char **split_pipes(char *str);

char redir_smb(int c);
int is_redir(char **token);
int redir_type(char *str);
int is_other_op(char c);
int find_next_redir(char *str);
int	check_redir(char **arg, int i);

char *extract_env_value(char *str);

#endif