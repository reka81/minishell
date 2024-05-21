/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:54:53 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/21 14:34:20 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_args_export(t_env *environment, t_hxh *final_linked)
{
	while (environment)
	{
		if (environment->variable)
		{
			ft_putstr_fd2("declare -x ", final_linked->output);
			ft_putstr_fd2(environment->variable, final_linked->output);
		}
		if (environment->value)
		{
			if (check_if_equal(environment->variable))
				ft_putstr_fd2(" \"", final_linked->output);
			ft_putstr_fd2(environment->value, final_linked->output);
			if (check_if_equal(environment->variable))
				ft_putstr_fd2("\"\n", final_linked->output);
			else
				ft_putstr_fd2("\n", final_linked->output);
		}
		environment = environment->next;
	}
}

void	store_var1(t_hxh *final_linked, char **variable, int *i, int *d)
{
	while (final_linked->value[*d][*i] && final_linked->value[*d][*i] != '=')
	{
		variable[0][*i] = final_linked->value[*d][*i];
		(*i)++;
	}
}

void	setting_var_and_val(char **variable,
	char **value, t_hxh *final_linked, int d)
{
	int	i;
	int	j;

	i = 0;
	*variable = zyalloc(strlen(final_linked->value[d]) + 2);
	store_var1(final_linked, variable, &i, &d);
	variable[0][i] = '\0';
	j = 0;
	if (i > 0 && final_linked->value[1][i])
	{
		if (final_linked->value[d][i] == '=')
			variable[0][i] = final_linked->value[d][i];
		i++;
		variable[0][i] = '\0';
	}
	*value = zyalloc(strlen(final_linked->value[d]) + 1);
	while (final_linked->value[d][i])
	{
		if (i > 0 && final_linked->value[d][i - 1] == '\0')
			break ;
		value[0][j] = final_linked->value[d][i];
		j++;
		i++;
	}
	value[0][j] = '\0';
}

int	cmp_w_dlm(char c, char s)
{
	char	*str;
	int		i;
	int		nothing;

	i = 0;
	str = "/*-+!@#$%^=";
	while (str[i])
	{
		if (str[i] == c)
		{
			if (c == '+' && s == '=')
				nothing = 0;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_dlm(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] == '\0')
			return (0);
		if (cmp_w_dlm(str[i], str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}
