/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_her3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:38:46 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/14 00:32:51 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expanding_her(char *value, int exit_status, t_env *environment)
{
	t_exp		*expander;
	t_counter	*count_num;

	expander = zyalloc(sizeof(t_exp));
	count_num = zyalloc(sizeof(t_counter));
	setting_values_her(expander, count_num, exit_status);
	expander->str2 = zyalloc(lenv(environment) + ft_strlen(value) + 1);
	while (value[count_num->i] != '$' && value[count_num->i])
	{
		expander->str2[count_num->i] = value[count_num->i];
		count_num->i++;
	}
	expander->str2[count_num->i] = '\0';
	rest_of_expanding6_her(count_num, value, expander, environment);
	return (expander->str2);
}

void	i_set(t_exp **expander, t_counter **count_num,
	int exit_status, int *flag)
{
	*expander = zyalloc(sizeof(t_exp));
	*count_num = zyalloc(sizeof(t_counter));
	*flag = 1;
	setting_values(*expander, *count_num, exit_status);
}

int	break_its(t_stack **a, t_exp *expander, t_env *environment)
{
	if (breaking_expanding(*a))
	{
		*a = (*a)->next;
		return (1);
	}
	expander->str2 = zyalloc(lenv(environment)
			+ ft_strlen((*a)->value) + 1);
	return (0);
}
