#include "../includes/minishell.h"

static void	free_partial(char **arr, int count)
{
	while (--count >= 0)
		free(arr[count]);
}

static char	*dup_or_exit(char *str, char **arr, int idx)
{
	arr[idx] = ft_strdup(str);
	if (!arr[idx])
	{
		free_partial(arr, idx);
		free(arr);
		return (NULL);
	}
	return (arr[idx]);
}

static char	**copy_remaining_tokens(char **tokens, char **new, int start_old, int start_new)
{
	int i = start_old;
	int j = start_new;

	while (tokens[i])
	{
		if (!dup_or_exit(tokens[i], new, j))
			return (NULL);
		i++;
		j++;
	}
	new[j] = NULL;
	return (new);
}

char	**build_new_tokens(char **tokens, char **arr, int pos, int arr_count)
{
	int		old_count;
	char	**new;
	int		i, k;

	old_count = count_tokens_array(tokens);
	new = malloc(sizeof(char *) * (old_count - 1 + arr_count + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		if (!dup_or_exit(tokens[i], new, i))
			return (NULL);
		i++;
	}
	k = 0;
	while (k < arr_count)
	{
		if (!dup_or_exit(arr[k], new, i))
			return (NULL);
		i++;
		k++;
	}
	return (copy_remaining_tokens(tokens, new, pos + 1, i));
}

// static char	**build_new_tokens(char **tokens, char **arr, int pos,
    // 	int arr_count)
    // {
    // 	char	**new;
    // 	int		old_count;
    // 	int		i;
    // 	int		j;
    // 	int		k;
    
    // 	old_count = count_tokens_array(tokens);
    // 	new = malloc(sizeof(char *) * (old_count - 1 + arr_count + 1));
    // 	if (!new)
    // 		return (NULL);
    // 	i = 0;
    // 	while (i < pos)
    // 	{
    // 		new[i] = tokens[i];
    // 		i++;
    // 	}
    // 	k = 0;
    // 	while (k < arr_count)
    // 	{
    // 		new[i] = ft_strdup(arr[k]);
    // 		if (!new[i])
    // 		{
    // 			while (--i >= 0 && i >= pos)
    // 				free(new[i]);
    // 			free(new);
    // 			return (NULL);
    // 		}
    // 		i++;
    // 		k++;
    // 	}
    // 	j = pos + 1;
    // 	while (j < old_count)
    // 		new[i++] = tokens[j++];
    // 	new[i] = NULL;
    // 	return (new);
    // }