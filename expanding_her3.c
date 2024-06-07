/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_her3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:38:46 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/07 16:39:54 by mettalbi         ###   ########.fr       */
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
	expander->str2 = zyalloc(100);
	while (value[count_num->i] != '$' && value[count_num->i])
	{
		expander->str2[count_num->i] = value[count_num->i];
		count_num->i++;
	}
	expander->str2[count_num->i] = '\0';
	rest_of_expanding6_her(count_num, value, expander, environment);
	return (expander->str2);
}
