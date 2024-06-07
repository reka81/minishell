/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_her2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:37:10 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:01:31 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rest_of_expanding3_her(char *value, t_counter *count_num,
			t_exp *expander, t_env *environment)
{
	char	*str;
	int		i;
	int		flag;
	int		star_of;

	star_of = count_num->i;
	flag = 0;
	i = 0;
	str = zyalloc(ft_strlen1(value) + 1);
	if (expander->dollar_flag == 1)
		tb_expanded_her(value, count_num, str, expander);
	str[count_num->j] = '\0';
	if (str[0] == '\0')
		expander->empty = 1;
	else
		expander->empty = 0;
	if (!ft_strcmp(str, "?"))
		expander->user = ft_itoa(expander->exit_status);
	else
		expander->user = ft_get_env(str, environment);
}

void	rest_of_expanding2_her(char *value, t_counter *count_num, char *str2)
{
	if (ft_isdigit (value[count_num->i]))
	{
		if (ft_isdigit (value[count_num->i]))
			count_num->i++;
		str2 = zyalloc(100);
		count_num->j = 0;
		while (value[count_num->i])
		{
			str2[count_num->j] = value[count_num->i];
			count_num->j++;
			count_num->i++;
			if (value[count_num->i - 1] == '$')
				break ;
		}
		str2[count_num->j] = '\0';
	}
}

void	rest_of_expanding_her(t_exp *expander, char *value,
			char *str2, t_counter *count_num)
{
	while (cmp_delim_her (value[count_num->i]))
	{
		if (value[count_num->i] == '?' && value[count_num->i - 1] == '$')
		{
			expander->exit_to_expand = 1;
			break ;
		}
		if (value[count_num->i] == '$')
			expander->dollar_flag = 1;
		else
			expander->dollar_flag = 0;
		str2[count_num->j] = value[count_num->i];
		count_num->j++;
		count_num->i++;
		count_num->e++;
	}
	str2[count_num->j] = '\0';
}

void	rest_of_expanding6_her(t_counter *count_num, char *value,
			t_exp *expander, t_env *environment)
{
	if (value[count_num->i] == '$')
	{
		while (value[count_num->i])
		{
			count_num->e = 0;
			count_num->d = 0;
			count_num->j = ft_strlen1(expander->str2);
			expander->str2[count_num->j] = '\0';
			rest_of_expanding_her(expander, value, expander->str2, count_num);
			rest_of_expanding2_her(value, count_num, expander->str2);
			count_num->k = ft_strlen1(expander->str2);
			count_num->j = 0;
			rest_of_expanding3_her(value, count_num, expander, environment);
			count_num->j = ft_strlen1(expander->str2);
			count_num->j -= 1;
			rest_of_expanding4_her(expander, expander->str2, count_num);
			rest_of_expanding5_her(value, count_num, expander->str2);
		}
		check_str_null_her(expander, value);
	}
}

void	setting_values_her(t_exp *expander,
	t_counter *count_num, int exit_status)
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
