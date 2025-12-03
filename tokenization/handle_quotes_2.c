/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:50 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/03 13:16:26 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static char	*remove_empty_quotes(char *str, int i)
// {
// 	char	*new_str;

// 	str[i] = 27;
// 	str[i + 1] = 27;
// 	new_str = ft_strdup(str);
// 	free(str);
// 	return (delete_quotes(new_str, 27));
// }

// static char	*remove_empty_quotes_arg(char *str, int i)
// {
// 	int		j;
// 	char	*new_str;

// 	str[i] = 48;
// 	str[i + 1] = ';';
// 	j = -1;
// 	new_str = malloc(sizeof(char) * ft_strlen(str));
// 	if (!new_str)
// 		exit_error("minishell: malloc failed", 1);
// 	while (++j < i)
// 		new_str[j] = str[j];
// 	while (str[j + 1])
// 	{
// 		new_str[j] = str[j + 1];
// 		j++;
// 	}
// 	new_str[j] = '\0';
// 	free(str);
// 	return (new_str);
// }
// before 28.11
// char *skip_empty_quotes(char *str, t_cmd *cmd)
// {
// (void)cmd;
// if (!str)
// return (NULL);
// int len = strlen(str);
// char *res = malloc(len + 1);
// if (!res)
//     exit_error("malloc failed", 1);

// int i = 0, j = 0;
// while (str[i])
// {
//     if (str[i] == '"' && str[i + 1] == '"')
//     {
//         i += 2;
//         continue ;
//     }
//     if (str[i] == '\'' && str[i + 1] == '\'')
//     {
//         i += 2;
//         continue ;
//     }
//     res[j++] = str[i++];
// }
// res[j] = '\0';
// return (res);
// }

int	is_empty_quotes_skippable(char *str, int i)
{
	char	prev;
	char	next;
	int		prev_is_sep;
	int		next_is_sep;

	if (i == 0)
		prev = ' ';
	else
		prev = str[i - 1];
	if (str[i + 2] == '\0')
		next = ' ';
	else
		next = str[i + 2];
	prev_is_sep = (prev == ' ' || prev == '\t' || prev == '\n'
			|| prev == '|' || prev == '<' || prev == '>');
	next_is_sep = (next == ' ' || next == '\t' || next == '\n'
			|| next == '|' || next == '<' || next == '>');
	return (prev_is_sep && next_is_sep);
}

char	*skip_empty_quotes(char *str, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*res;

	(void)cmd;
	if (!str)
		return (NULL);
	res = malloc(strlen(str) + 1);
	if (!res)
		exit_error("malloc failed", 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\''
				&& str[i + 1] == '\''))
			i = handle_quote_pair(str, res, i, &j);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

// after changes """"+smth ->working and cut
// char *skip_empty_quotes(char *str, t_cmd *cmd)
// {
//     (void)cmd;
//     if (!str)
//         return (NULL);

//     int len = strlen(str);
//     char *res = malloc(len + 1);
//     if (!res)
//         exit_error("malloc failed", 1);

//     int i = 0, j = 0;
//     while (str[i])
//     {
//         if ((str[i] == '"' && str[i + 1] == '"') ||
//             (str[i] == '\'' && str[i + 1] == '\''))
//         {
//             char prev = (i == 0) ? ' ' : str[i - 1];
//             char next = (str[i + 2] == '\0') ? ' ' : str[i + 2];
//             int prev_is_space = (prev == ' ' || prev == '\t' || prev == '\n'
		// || prev == '|' || prev == '<' || prev == '>' );
//             int next_is_space = (next == ' ' || next == '\t' || next == '\n'
		// || next == '|' || next == '<' || next == '>' );
//             if (prev_is_space && next_is_space)
//             {
//                 i += 2;
//                 continue ;
//             }
//             res[j++] = str[i++];
//             continue ;
//         }
//         res[j++] = str[i++];
//     }
//     res[j] = '\0';
//     return (res);
// }

// char	*delete_quotes(char *str, char c)
// {
// 	int		len = 0, i = 0, j;
// 	char	*temp;

// 	len = 0, i = 0, j = 0;
// 	while (str[i])
// 		if (str[i++] != c)
// 			len++;
// 	temp = malloc(len + 1);
// 	if (!temp)
// 		exit_error("malloc failed", 1);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != c)
// 			temp[j++] = str[i];
// 		i++;
// 	}
// 	temp[j] = '\0';
// 	free(str);
// 	return (temp);
// }
