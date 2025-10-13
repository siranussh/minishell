#include "tokenization.h"

int	exp_strcmp(char *s1, char *s2)
{
    size_t i;

    i = 0;
    if (!s1 || !s2)
        return (1);
    while(s2[i] && s2[i] != '=')
        i++;
    if (ft_strlen(s1) != i)
        return (1);
    i = 0;
    while (s1[i] && s2[i] && s2[i] != '=')
    {
        if(s1[i] != s2[i])
            return (1);
        i++;
    }
    return (0);
}

char *exp_strjoin(char *s1, char *s2, size_t i, size_t j)
{
    char *new;
    size_t size1;

    size1 = ft_strlen(s1);
    if (s1[size1 - 1] == 34 || s1[size1 - 1] == 39)
        size1--;
    new = (char *)malloc(sizeof(char) * (size1 + ft_strlen(s2) + 1));
    if (!new)
        return (0);
    while (s1[i] && i < size1)
    {
        new[i] = s1[i];
        i++;
    }
    while(s2[j])
    {
        new[i + j] = s2[j];
        j++;
    }
    new[i + j] = '\0';
    return (new);
}