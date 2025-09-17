#ifndef TOKENAZIATION_H
#define TOKENAZIATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define EMPTY_QUOTE_MARK 27 



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
int exit_error(char *str, int code);

int check_quotes_type(char *str);
int find_closing_quote(int i, char *str, char c);
char *skip_empty_quotes(char *str, t_cmd *cmd);
char *delete_quotes(char *str, char c);
int is_other_op(char c);
int count_tokens(char *str);
#endif