#ifndef TOKENAZIATION_H
#define TOKENAZIATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int skip_quotes(int i, char *str, char c);
int exit_error(char *str, int code);

#endif