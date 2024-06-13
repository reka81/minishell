/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:37:35 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/13 18:51:28 by mettalbi         ###   ########.fr       */
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
}

int	check_pipings(char *str)
{
	int	i;

	i = 0;
	while (str[i])
}

int	checking_parsing(t_stack *lst)
{
	while (lst)
	{
		if (lst->type == 3)
		{
			if (ft_strlen(lst->value) > 1)
				return (1);
			else if (check_confliction(lst->value))
				return (1);
			else if (check_pipings(lst->value))
				return (1);
		}
	}
}
