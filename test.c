/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:37:35 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/13 20:01:48 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_confliction(char *str)
{
	char	c;
	int		i;

	i = 0;
	c = str[0];
	while (str[i])
	{
		if (c != str[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_pipings(t_stack *lst)
{
	if (lst->type == 3 && ft_strcmp (lst->value, "|") == 0)
	{
		if (lst->next)
		{
			if (lst->next->type == 3 && ft_strcmp (lst->next->value, "|") == 0)
				return (1);
			else if (lst->next->type == 6)
			{
				if (lst->next->next)
				{
					lst = lst->next->next;
					if (lst->type == 3
						&& ft_strcmp (lst->value, "|") == 0)
						return (1);
				}
				else
					return (1);
			}
		}
	}
	return (0);
}

int	checking_parsing(t_stack *lst)
{
	while (lst)
	{
		if (lst->type == 3)
		{
			if (ft_strlen(lst->value) > 2)
				return (1);
			else if (check_confliction(lst->value))
				return (1);
			else if (check_pipings(lst))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}
