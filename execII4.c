/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:24:37 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/11 17:16:08 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cheak_n(char *str)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) == 1)
		return (1);
	while (str[i])
	{
		if ((str[0] != '-' || str[i] != 'n'))
		{
			return (1);
		}
		i++;
		j++;
	}
	return (2);
}

int	ft_strdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo2(int *i, t_hxh *lst)
{
	while (lst->value[(*i)])
	{
		if (ft_cheak_n(lst->value[(*i)]) == 2)
			(*i)++;
		else
			break ;
	}
}

int	cmp_w_dlm2(char c)
{
	char	*str;
	int		i;

	i = 0;
	str = "/*-!@#$%^";
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
