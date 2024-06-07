/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:22 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:26:04 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_name1(char *str, t_stack *tmp, t_stack **lst)
{
	while (tmp->next != NULL)
	{
		if (tmp->next->type != 6)
		{
			if (tmp->next->type != 3)
			{
				if (!str)
					str = ft_strjoin(tmp->value, tmp->next->value);
				else
					str = ft_strjoin(str, tmp->next->value);
			}
			else
			{
				(1) && (str = tmp->value, *lst = tmp);
				break ;
			}
		}
		else
		{
			(1) && (str = tmp->value, *lst = tmp);
			break ;
		}
		(1) && (tmp = tmp->next, *lst = tmp);
	}
	return (str);
}

char	*file_name(t_stack **lst)
{
	char	*str;
	t_stack	*tmp;

	str = NULL;
	tmp = NULL;
	if ((*lst)->next->type == 6)
		tmp = (*lst)->next->next;
	else
		tmp = (*lst)->next;
	if (tmp->next != NULL)
		str = file_name1(str, tmp, lst);
	else
	{
		str = tmp->value;
		*lst = tmp;
	}
	return (str);
}
