/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:54:53 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/04 20:02:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*sort_envi(t_env *lst)
{
	char	*swp_var;
	char	*swp_val;
	t_env	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (ft_strcmp(lst->variable, lst->next->variable) > 0)
		{
			swp_var = lst->variable;
			swp_val = lst->value;
			lst->variable = lst->next->variable;
			lst->value = lst->next->value;
			lst->next->variable = swp_var;
			lst->next->value = swp_val;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

void	no_args_export(t_hxh *final_linked, char **env)
{
	t_env	*tmp;

	tmp = NULL;
	filling_env(env, &tmp);
	if (tmp)
		tmp = sort_envi(tmp);
	while (tmp)
	{
		if (tmp->variable)
		{
			ft_putstr_fd2("declare -x ", final_linked->output);
			ft_putstr_fd2(tmp->variable, final_linked->output);
		}
		if (tmp->value)
		{
			if (check_if_equal(tmp->variable))
				ft_putstr_fd2("\"", final_linked->output);
			ft_putstr_fd2(tmp->value, final_linked->output);
			if (check_if_equal(tmp->variable))
				ft_putstr_fd2("\"\n", final_linked->output);
			else
				ft_putstr_fd2("\n", final_linked->output);
		}
		tmp = tmp->next;
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
