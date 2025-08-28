#include "tokenization.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*duplicate;

	i = 0;
	size = ft_strlen(s1);
	duplicate = malloc(sizeof(char) * (size + 1));
	if (!duplicate)
		return (NULL);
	while (s1[i])
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	real_len;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	real_len = s_len - start;
	if (real_len > len)
		real_len = len;
	str = malloc(sizeof(char) * (real_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < real_len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
