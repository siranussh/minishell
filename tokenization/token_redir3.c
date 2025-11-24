#include "../includes/minishell.h"

static int	count_tokens_array(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

static char	**build_new_tokens(char **tokens, char **arr, int pos, int arr_count)
{
	char	**new;
	int		old_count;
	int		i;
	int		j;
	int		k;

	old_count = count_tokens_array(tokens);
	new = malloc(sizeof(char *) * (old_count - 1 + arr_count + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		new[i] = tokens[i];
		i++;
	}
	k = 0;
	while (k < arr_count)
		new[i++] = arr[k++];
	j = pos + 1;
	while (j < old_count)
		new[i++] = tokens[j++];
	new[i] = NULL;
	return (new);
}

void	replace_token_with_array(char ***tokens, int pos, char **arr, int arr_count)
{
	char	**new;

	if (!tokens || !(*tokens) || !arr)
		return ;
	new = build_new_tokens(*tokens, arr, pos, arr_count);
	if (!new)
		return ;
	free((*tokens)[pos]);
	free(*tokens);
	*tokens = new;
}

static int	process_redir_token(t_cmd *cmd, int i)
{
	int		new_count;
	char	**parts;

	new_count = 0;
	parts = split_redirs_token(cmd->tokens[i], &new_count);
	if (!parts)
		return (0);
	if (new_count > 1)
	{
		replace_token_with_array(&cmd->tokens, i, parts, new_count);
		free(parts);
		return (1); // token replaced
	}
	free(parts);
	return (0); // token not replaced
}

void	normalize_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->tokens && cmd->tokens[i])
	{
		if (strchr(cmd->tokens[i], '<') || strchr(cmd->tokens[i], '>'))
		{
			if (process_redir_token(cmd, i))
				continue ;
		}
		i++;
	}
}
