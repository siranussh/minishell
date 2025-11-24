#include "../includes/minishell.h"

char	**remove_token(char **tokens, int index)
{
	int		count;
	int		i;
	int		j;
	char	**result;

	if (!tokens)
		return (NULL);
	count = 0;
	while (tokens[count])
		count++;
	result = ft_calloc(sizeof(char *), count);// one less element
	if (!result)
		exit_error("malloc failed", 1);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != index)
			result[j++] = ft_strdup(tokens[i]);
		free(tokens[i++]);
	}
	free(tokens);
	return (result);
}

char	**add_token(char **tokens, char *new, int j)
{
	char	**result;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (tokens[i])
		i++;
	result = ft_calloc(sizeof(char *), i + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (tokens[k])
	{
		result[i] = ft_strdup(tokens[k]);
		free(tokens[k]);
		i++;
		k++;
		if (k == j)
			result[i++] = new;
	}
	free(tokens);
	return (result);
}

char	**split_redirection_start(char **tokens, int j, char c)
{
	char	*temp;
	int		pos;

	pos = find_next_redir(tokens[j]);
	if (pos < 0)
		return (tokens);
	tokens = add_token(tokens, ft_substr(tokens[j], 0, pos), j + 1);
	temp = ft_strdup(ft_strchr(tokens[j], c));
	free(tokens[j]);
	tokens[j] = temp;
	return (split_redirection_tokens(tokens, j, c, 2));
}


char	**split_redirection_tokens(char **tokens, int j, char c, int k)
{
	int	i;

	i = 0;
	if (tokens[j][i] == '2' && tokens[j][i + 1] == '>')
		i++;
	while (tokens[j][i] == c)
		i++;
	if (!tokens[j][i])
		return (tokens);
	if (i == 0)
		return (split_redirection_start(tokens, j, c));
	return (split_redirection_parts(tokens, j, i, k));
}

char	**split_redirection_parts(char **tokens, int j, int i, int k)
{
	int		next;
	char	*part1;
	char	*part2;
	char	*part3;

	part1 = ft_substr(tokens[j], 0, i);
	tokens = add_token(tokens, part1, j + k);
	k++;
	next = find_next_redir(tokens[j]);
	part2 = ft_substr(tokens[j], i, next - i);
	tokens = add_token(tokens, part2, j + k);
	k++;
	if (tokens[j][next])
	{
		part3 = ft_substr(tokens[j], next, ft_strlen(tokens[j]) - next);
		tokens = add_token(tokens, part3, j + k);
	}
	tokens = remove_token(tokens, j);
	return (tokens);
}





