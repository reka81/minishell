/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:42 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/07 18:04:12 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_delm(t_stack **tmp, t_stack **lst, char *str, int *flag)
{
	while ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type == 1 || (*tmp)->next->type == 2)
			*flag = 1;
		if ((*tmp)->next->type != 6)
		{
			if ((*tmp)->next->type != 3)
				str = str_setting(tmp, str);
			else
			{
				(1) && (str = (*tmp)->value, *lst = (*tmp));
				break ;
			}
		}
		else
		{
			(1) && (str = (*tmp)->value, *lst = (*tmp));
			break ;
		}
		(1) && ((*tmp) = (*tmp)->next, *lst = (*tmp));
	}
	return (str);
}

char	*next_space(t_stack **tmp, char *str, t_stack **lst, int *flag)
{
	*tmp = (*tmp)->next->next;
	if ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type != 6)
		{
			str = join_delm(tmp, lst, str, flag);
		}
		else
		{
			str = (*tmp)->value;
			*lst = (*tmp);
		}
	}
	else
	{
		if ((*tmp)->type == 1 || (*tmp)->type == 2)
			*flag = 1;
		str = (*tmp)->value;
		*lst = (*tmp);
	}
	return (str);
}

char	*join_delm1(t_stack **tmp, t_stack **lst, char *str, int *flag)
{
	while ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type == 1 || (*tmp)->next->type == 2)
			*flag = 1;
		if ((*tmp)->next->type != 6)
		{
			if ((*tmp)->next->type != 3)
			{
				if (!str)
					str = ft_strjoin((*tmp)->value,
							(*tmp)->next->value);
				else
					str = ft_strjoin(str, (*tmp)->next->value);
			}
			else
			{
				(1) && (str = (*tmp)->value, *lst = (*tmp));
				break ;
			}
		}
		else
			break ;
		(1) && ((*tmp) = (*tmp)->next, *lst = (*tmp));
	}
	return (str);
}

char	*next_not_space(t_stack **tmp, char *str, t_stack **lst, int *flag)
{
	(*tmp) = (*tmp)->next;
	if ((*tmp)->next != NULL)
	{
		if ((*tmp)->next->type != 6)
		{
			str = join_delm1(tmp, lst, str, flag);
		}
		else
		{
			if ((*tmp)->type == 1 || (*tmp)->type == 2)
				*flag = 1;
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

char	*herdog_delm(t_stack **lst, int *flag)
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
				str = next_space(&tmp, str, lst, flag);
				if (str)
					break ;
			}
			else if (tmp->next->type != 6)
			{
				str = next_not_space(&tmp, str, lst, flag);
				if (str)
					break ;
			}
		}
		tmp = tmp->next;
	}
	return (str);
}
