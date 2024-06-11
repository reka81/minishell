/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:31:47 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/10 17:50:18 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_var(t_hxh *final_linked, int *i, char *variable)
{
	while (final_linked->value[0][*i] && final_linked->value[0][*i] != '='
		&& final_linked->value[0][*i] != '+')
	{
		variable[*i] = final_linked->value[0][*i];
		(*i)++;
	}
}

void	store_val(t_hxh *final_linked, int *i, int *j, char *value)
{
	while (final_linked->value[0][*i])
	{
		value[*j] = final_linked->value[0][*i];
		(*j)++;
		(*i)++;
	}
}

void	join_or_n(t_hxh *final_linked, t_env *tmp, char *value)
{
	if (tmp)
	{
		if (!check_if_pls(final_linked->value))
		{
			tmp->value = value;
		}
		else
		{
			if (!check_if_equal(tmp->variable))
				tmp->variable = ft_strjoin(tmp->variable, "=");
			tmp->value = ft_strjoin(tmp->value, value);
		}
	}
}

void	afterwards_assignment(t_hxh *final_linked,
	t_env *environment, t_env *tmp)
{
	char	*variable;
	char	*value;
	int		j;
	int		i;

	j = 0;
	i = 0;
	variable = zyalloc(ft_strlen(final_linked->value[0]) + 1);
	store_var(final_linked, &i, variable);
	variable[i] = '\0';
	if (i > 0)
	{
		if (final_linked->value[0][i] == '+')
			i++;
		i++;
	}
	j = 0;
	value = zyalloc(ft_strlen(final_linked->value[0]) + 1);
	store_val(final_linked, &i, &j, value);
	value[j] = '\0';
	tmp = check_if_var2(environment, variable);
	join_or_n(final_linked, tmp, value);
}

int	check_if_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
