/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:42 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/31 16:55:11 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_delm(t_stack **tmp, t_stack **lst, char *str)
{
	while ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type != 6)
		{
			if (!str)
				str = ft_strjoin((*tmp)->value,
						(*tmp)->next->value);
			else
				str = ft_strjoin(str, (*tmp)->next->value);
		}
		else
			break ;
		(*tmp) = (*tmp)->next;
		*lst = (*tmp);
	}
	return (str);
}

char	*next_space(t_stack **tmp, char *str, t_stack **lst)
{
	*tmp = (*tmp)->next->next;
	if ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type != 6)
		{
			str = join_delm(tmp, lst, str);
		}
		else
		{
			str = (*tmp)->value;
			*lst = (*tmp);
		}
	}
	else
	{
		str = (*tmp)->value;
		*lst = (*tmp);
	}
	return (str);
}

char	*join_delm1(t_stack **tmp, t_stack **lst, char *str)
{
	while ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type != 6)
		{
			if (!str)
				str = ft_strjoin((*tmp)->value,
						(*tmp)->next->value);
			else
				str = ft_strjoin(str, (*tmp)->next->value);
		}
		else
			break ;
		(*tmp) = (*tmp)->next;
		*lst = (*tmp);
	}
	return (str);
}

char	*next_not_space(t_stack **tmp, char *str, t_stack **lst)
{
	(*tmp) = (*tmp)->next;
	if ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type != 6)
		{
			str = join_delm1(tmp, lst, str);
		}
		else
		{
			str = (*tmp)->value;
			*lst = (*tmp);
		}
	}
	else
	{
		str = (*tmp)->value;
		*lst = *tmp;
	}
	return (str);
}

char	*herdog_delm(t_stack **lst)
{
	t_stack	*tmp;
	char	*str;

	tmp = *lst;
	str = NULL;
	while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
	{
		if (ft_strcmp(tmp->value, "<<") == 0)
		{
			if (tmp->next->type == 6)
			{
				str = next_space(&tmp, str, lst);
			}
			else if (tmp->next->type != 6)
			{
				str = next_not_space(&tmp, str, lst);
			}
		}
		tmp = tmp->next;
	}
	return (str);
}
