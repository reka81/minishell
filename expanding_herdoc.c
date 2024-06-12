/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_herdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 23:41:59 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/12 15:14:49 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_str_null_her(t_exp *expander, char *value)
{
	if (expander->str2[0] == '\0')
	{
		value = expander->str2;
	}
	if (expander->str2 != NULL)
	{
		value = expander->str2;
	}
}

int	cmp_delim_her(char c)
{
	int		i;
	char	*delim;

	i = 0;
	delim = "'\"~!@#$%^&*-+=.?,";
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	rest_of_expanding5_her(char *value, t_counter *count_num, char *str2)
{
	while (value[count_num->i])
	{
		if (value[count_num->i] == '$')
		{
			if (value[count_num->i + 1])
				break ;
		}
		str2[count_num->j] = value[count_num->i];
		count_num->i++;
		count_num->j++;
	}
	str2[count_num->j] = '\0';
}

void	rest_of_expanding4_her(t_exp *expander, char *str2,
			t_counter *count_num)
{
	int	i;

	i = 0;
	if (expander->user)
	{
		if (expander->user[count_num->d])
			str2[count_num->j] = '\0';
		while (expander->user[count_num->d])
		{
			i = 1;
			str2[count_num->j] = expander->user[count_num->d];
			(1) && (count_num->d++, count_num->j++);
		}
	}
	if (count_num->d > 0)
		str2[count_num->j] = '\0';
	count_num->j = ft_strlen1(str2);
	if (expander->empty == 1)
		expander->empty = 1;
	else if (i == 0)
	{
		count_num->j -= count_num->e;
		str2[count_num->j] = '\0';
	}
	str2[count_num->j] = '\0';
}

void	tb_expanded_her(char *value, t_counter *count_num,
	char *str, t_exp *expander)
{
	while (value[count_num->i] && !cmp_delim_her(value[count_num->i]))
	{
		if (value[count_num->i] == ' ')
			break ;
		str[count_num->j] = value[count_num->i];
		count_num->i++;
		count_num->j++;
	}
	if (value[count_num->i] == '?' && expander->exit_to_expand == 1)
	{
		str[count_num->j] = value[count_num->i];
		count_num->j++;
		count_num->i++;
	}
}
