/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:15:07 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/03 22:11:05 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_pls2(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '=' && str[j])
	{
		if (str[j] == '+')
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strmcpy(char *path, char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (NULL);
	path = zyalloc(ft_strlen1(value) + 1);
	while (value[i])
	{
		path[i] = value[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

int	is_apath(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*new_var_woutpls(char *variable)
{
	char	*new;
	int		i;

	new = zyalloc(ft_strlen1(variable) + 1);
	i = 0;
	while (variable[i] != '+' && variable[i])
	{
		new[i] = variable[i];
		i++;
	}
	if (variable[i] == '+' && variable[i + 1] == '=')
	{
		new[i] = '=';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*new_var_woutequal(char *variable)
{
	char	*new;
	int		i;

	new = zyalloc(ft_strlen1(variable) + 1);
	i = 0;
	while (variable[i] != '=' && variable[i])
	{
		new[i] = variable[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
