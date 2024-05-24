/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:26:44 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/24 13:39:30 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rederection_handling(t_stack **lst, t_int *lor_int, char *chen)
{
	int		i;
	char	**splitting;
	int		j;

	i = 0;
	j = 0;
	splitting = NULL;
	if ((*lst) != NULL && ((*lst)->type == 1
			|| (*lst)->type == 2 || (*lst)->type == 0))
	{
		if ((*lst)->next)
		{
			if ((*lst)->next->type == 6)
				if_next_is_space(lst, splitting, lor_int, &j);
			else
				if_next_not_space(lst, lor_int);
		}
		else
			if_next_is_null(lst, splitting, lor_int, &j);
	}
	else if (*lst != NULL && (*lst)->type == 3)
		chen = opening_rederections(lst, lor_int, chen, i);
	if (*lst)
	{
			(*lst) = (*lst)->next;
	}
	return (chen);
}

void	increment_to_pipe(t_stack **lst)
{
	if (*lst && ft_strcmp((*lst)->value, "|") != 0)
	{
		while (*lst && ft_strcmp((*lst)->value, "|") != 0)
			*lst = (*lst)->next;
		if (*lst)
		{
			if (ft_strcmp((*lst)->value, "|") == 0)
				(*lst) = (*lst)->next;
		}
	}
	else
		(*lst) = (*lst)->next;
}

void	creating_list(t_stack **lst, t_int *lor_int)
{
	lor_int->str = zyalloc(sizeof(char *) * 100);
	lor_int->out = 1;
	lor_int->in = 0;
	lor_int->fd = 0;
	lor_int->z = 0;
	lor_int->k = 0;
	while (*lst != NULL && ft_strcmp((*lst)->value, "|") != 0)
	{
		lor_int->chen = NULL;
		lor_int->chen = rederection_handling(lst, lor_int, lor_int->chen);
		if (lor_int->k == 20 || lor_int->k == 30)
		{
			if (lor_int->k == 20)
				printf("is an ambigious redirect\n");
			break ;
		}
		if (lor_int->chen != NULL)
		{
			if (ft_strcmp("broken", lor_int->chen) == 0)
				break ;
			printf("%s\n", lor_int->chen);
			break ;
		}
		if (lst == NULL)
			break ;
	}
}

t_hxh	*ft_store(t_stack *lol)
{
	t_hxh	*l;
	t_int	*lor_int;
	t_stack	*lst;

	lst = lol;
	l = NULL;
	lor_int = zyalloc(sizeof(t_int));
	lor_int->i = 0;
	lor_int->n = 1;
	lor_int->chen = NULL;
	while (lst != NULL)
	{
		creating_list(&lst, lor_int);
		lor_int->str[lor_int->z] = NULL;
		ft_lstadd_back1(&l, ft_lstnew1(lor_int, lor_int->chen));
		if (lst == NULL)
		{
			break ;
		}
		increment_to_pipe(&lst);
	}
	return (l);
}
