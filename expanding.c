/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:36:59 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/12 15:26:54 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rest_of_expanding5(t_stack *a, t_counter *count_num, char *str2)
{
	while (a->value[count_num->i])
	{
		if (a->value[count_num->i] == '$')
		{
			if (a->value[count_num->i + 1])
				break ;
		}
		str2[count_num->j] = a->value[count_num->i];
		count_num->i++;
		count_num->j++;
	}
	str2[count_num->j] = '\0';
}

void	check_str_null(t_exp *expander, t_stack *a)
{
	if (expander->str2[0] == '\0')
	{
		expander->str2 = NULL;
		a->value = expander->str2;
	}
	if (expander->str2 != NULL)
	{
		a->value = expander->str2;
		a->did_expand = 40;
	}
}

void	rest_of_expanding6(t_counter *count_num, t_stack *a,
			t_exp *expander, t_env *environment)
{
	(void)environment;
	if (a->value[count_num->i] == '$')
	{
		while (a->value[count_num->i])
		{
			count_num->e = 0;
			count_num->d = 0;
			count_num->j = ft_strlen1(expander->str2);
			expander->str2[count_num->j] = '\0';
			rest_of_expanding(expander, a, expander->str2, count_num);
			rest_of_expanding2(a, count_num, expander->str2);
			count_num->k = ft_strlen1(expander->str2);
			count_num->j = 0;
			rest_of_expanding3(a, count_num, expander, environment);
			count_num->j = ft_strlen1(expander->str2);
			count_num->j -= 1;
			rest_of_expanding4(expander, expander->str2, count_num);
			rest_of_expanding5(a, count_num, expander->str2);
		}
		check_str_null(expander, a);
	}
}

void	setting_values(t_exp *expander, t_counter *count_num, int exit_status)
{
	expander->dollar_flag = 50;
	expander->exit_to_expand = 0;
	expander->user = NULL;
	count_num->k = 0;
	count_num->e = 0;
	count_num->d = 0;
	count_num->j = 0;
	count_num->i = 0;
	expander->exit_status = exit_status;
}

void	expanding(t_stack *a, int exit_status, t_env *environment)
{
	int			flag;
	t_counter	*count_num;
	t_exp		*expander;

	i_set(&expander, &count_num, exit_status, &flag);
	while (a)
	{
		while (a)
		{
			count_num->i = 0;
			if ((a->type == 1 || a->type == 0) && a->should_be_exp != 1)
			{
				if (breaking_expanding(a))
				{
					a = a->next;
					break ;
				}
				expander->str2 = zyalloc(lenv(environment)
						+ ft_strlen(a->value) + 1);
				while (a->value[count_num->i] != '$' && a->value[count_num->i])
					(1) && (expander->str2[count_num->i] = a->value[count_num->i]
						, count_num->i++);
				expander->str2[count_num->i] = '\0';
				rest_of_expanding6(count_num, a, expander, environment);
			}
			a = a->next;
		}
	}
}
