/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:25:15 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/13 18:04:54 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_hxh *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int	ft_lstsize1(t_env *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int	ft_lstsize2(t_stack *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		size += (count_strings(lst->value, ' ') + 1);
		lst = lst->next;
	}
	return (size);
}

int	ft_lstsize3(t_hxh *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst->value[size])
	{
		size++;
	}
	return (size);
}
