/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:04:55 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/21 15:09:25 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rest_of_expanding(t_exp *expander, t_stack *a,
			char *str2, t_counter *count_num)
{
	while (cmp_delim (a->value[count_num->i]))
	{
		if (a->value[count_num->i] == '?' && a->value[count_num->i - 1] == '$')
		{
			expander->exit_to_expand = 1;
			break ;
		}
		if (a->value[count_num->i] == '$')
			expander->dollar_flag = 1;
		else
			expander->dollar_flag = 0;
		str2[count_num->j] = a->value[count_num->i];
		count_num->j++;
		count_num->i++;
		count_num->e++;
	}
	str2[count_num->j] = '\0';
}

void	rest_of_expanding2(t_stack *a, t_counter *count_num, char *str2)
{
	if (ft_isdigit (a->value[count_num->i]))
	{
		if (ft_isdigit (a->value[count_num->i]))
			count_num->i++;
		str2 = zyalloc(100);
		count_num->j = 0;
		while (a->value[count_num->i])
		{
			str2[count_num->j] = a->value[count_num->i];
			count_num->j++;
			count_num->i++;
			if (a->value[count_num->i - 1] == '$')
				break ;
		}
		str2[count_num->j] = '\0';
	}
}

void	rest_of_expanding3(t_stack *a, t_counter *count_num,
			t_exp *expander, t_env *environment)
{
	char	*str;

	str = zyalloc(ft_strlen1(a->value) + 1);
	if (expander->dollar_flag == 1)
	{
		while (a->value[count_num->i] && !cmp_delim(a->value[count_num->i]))
		{
			str[count_num->j] = a->value[count_num->i];
			count_num->i++;
			count_num->j++;
		}
		if (a->value[count_num->i] == '?' && expander->exit_to_expand == 1)
		{
			str[count_num->j] = a->value[count_num->i];
			count_num->j++;
			count_num->i++;
		}
	}
	str[count_num->j] = '\0';
	if (!ft_strcmp(str, "?"))
		expander->user = ft_itoa(expander->exit_status);
	else
		expander->user = ft_get_env(str, environment);
}

void	rest_of_expanding4(t_exp *expander, char *str2, t_counter *count_num)
{
	int	i;

	i = 0;
	if (expander->user)
	{
		str2[count_num->j] = '\0';
		while (expander->user[count_num->d])
		{
			i = 1;
			str2[count_num->j] = expander->user[count_num->d];
			count_num->d++;
			count_num->j++;
		}
	}
	if (count_num->d > 0)
		str2[count_num->j] = '\0';
	count_num->j = ft_strlen1(str2);
	if (i == 0)
	{
		count_num->j -= count_num->e;
		str2[count_num->j] = '\0';
	}
	str2[count_num->j] = '\0';
}
