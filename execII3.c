/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:12 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/04 20:14:58 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_w_dlm2(char c)
{
	char	*str;
	int		i;

	i = 0;
	str = "/*-!@#$%^";
	while (str[i])
	{
		if (str[i] == c)
			return (1);
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
		{
			if (cmp_w_dlm2(str[i]))
				return (1);
			return (0);
		}
		if (cmp_w_dlm(str[i], str[i + 1]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_exit(t_hxh *lst)
{
	if (!ft_strcmp(lst->value[0], "exit"))
	{
		if (lst->value[1])
		{
			if (ft_strdigit(lst->value[1]) == 1)
				exit(atoi(lst->value[1]));
			else
			{
				dprintf(2, "bash: exit: %s: numeric argument required",
					lst->value[1]);
				exit(255);
			}
		}
		else
			exit(0);
	}
}

void	exp_n_valid(t_hxh *final_linked, char *value)
{
	dprintf(2, "bash: export: `%s': not a valid identifier\n", value);
	if (final_linked->value[2])
		dprintf(2, "bash: export: `%s': not a valid identifier\n",
			final_linked->value[2]);
}
