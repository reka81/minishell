/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:36:59 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/18 17:56:26 by mettalbi         ###   ########.fr       */
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
		free(str2);
		str2 = malloc(100);
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
			t_exp *expander, int exit_status, t_env *environment)
{
	char	*str;

	str = malloc(ft_strlen1(a->value) + 1);
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
		expander->user = ft_itoa(exit_status);
	else
		expander->user = ft_get_env(str, environment);
	free(str);
}

void	rest_of_expanding4(t_exp *expander, char *str2, t_counter *count_num)
{
	int i;
	
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

void	rest_of_expanding6(t_counter *count_num, t_stack *a,
			t_exp *expander, char *str2, t_env *environment)
{
	if (a->value[count_num->i] == '$')
	{
		count_num->e = 0;
		while (a->value[count_num->i])
		{
			count_num->d = 0;
			count_num->j = ft_strlen1(str2);
			str2[count_num->j] = '\0';
			rest_of_expanding(expander, a, str2, count_num);
			rest_of_expanding2(a, count_num, str2);
			count_num->k = ft_strlen1(str2);
			count_num->j = 0;
			rest_of_expanding3(a, count_num, expander, expander->exit_status, environment);
			count_num->j = ft_strlen1(str2);
			count_num->j -= 1;
			rest_of_expanding4(expander, str2, count_num);
			rest_of_expanding5(a, count_num, str2);
		}
		if(str2[0] == '\0')
		{
			free(str2);
			str2 = NULL;
			a->value = str2;
		}
		if (str2 != NULL)
		{
			free(a->value);
			a->value = str2;
			a->did_expand = 40;
		}
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
	char		*str2;
	int			flag;
	t_counter	*count_num;
	t_exp		*expander;

	expander = malloc(sizeof(t_exp));
	count_num = malloc(sizeof(t_counter));
	flag = 1;
	setting_values(expander, count_num, exit_status);
	while (a)
	{
		count_num->i = 0;
		if ((a->type == 1 || a->type == 0) && a->should_be_exp != 1)
		{
			str2 = malloc(100);
			while (a->value[count_num->i] != '$' && a->value[count_num->i])
			{
				str2[count_num->i] = a->value[count_num->i];
				count_num->i++;
			}
			str2[count_num->i] = '\0';
			rest_of_expanding6(count_num, a, expander, str2, environment);
		}
		a = a->next;
	}
}
