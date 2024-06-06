/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zyalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:23:23 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/06 21:24:07 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back4(t_garbage **lst, t_garbage *newnode)
{
	t_garbage	*start;

	if (!lst)
		return ;
	start = *lst;
	if (*lst)
	{
		while (start->next)
			start = start->next;
		start->next = newnode;
	}
	else
		*lst = newnode;
}

t_garbage	*ft_lstnew8(char *address)
{
	t_garbage	*s1;

	s1 = (t_garbage *)malloc(sizeof(t_garbage));
	if (!s1)
		return (NULL);
	s1->address = address;
	s1->next = NULL;
	return (s1);
}

void	*zyalloc(long long size)
{
	static t_garbage	*gorg;
	void				*address;

	address = malloc(size);
	if (!address)
	{
		free(address);
		exit(1);
	}
	ft_lstadd_back4(&gorg, ft_lstnew8(address));
	return (address);
}

t_env	*ft_lstnew5(char *variable, char *value)
{
	t_env	*s1;

	s1 = zyalloc(sizeof(t_env));
	if (!s1)
		return (NULL);
	s1->variable = variable;
	s1->value = value;
	s1->next = NULL;
	return (s1);
}
