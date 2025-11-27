/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:55 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/27 20:53:32 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_19digits(char *s, int sign)
{
	char	*max;
	char	*min;
	int		len;

	max = "9223372036854775807";
	min = "9223372036854775808";
	len = 0;
	while (*s == '0')
		s++;
	while (s[len])
	{
		if (!ft_isdigit(s[len]))
			return (1);
		len++;
	}
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (sign == 1 && ft_strcmp(s, max) > 0)
		return (1);
	if (sign == -1 && ft_strcmp(s, min) > 0)
		return (1);
	return (0);
}

int	is_long_overflow(char *s)
{
	int	sign;

	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (check_19digits(s, sign) == 1)
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}
