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

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	start = 0;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[end]) && end >= start)
		end--;
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)s + i);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*c;

	if (count == 0 || size == 0)
		return (malloc(0));
	c = malloc(count * size);
	if (!c)
		return (NULL);
	ft_memset(c, 0, count * size);
	return (c);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	n;

	str = (unsigned char *)b;
	n = c;
	while (len--)
	{
		*str = n;
		str++;
	}
	return (b);
}