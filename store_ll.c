/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:26:44 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/30 20:51:50 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cheack_if_space_or_not(t_stack **lst, char **splitting,
	t_int *lor_int, int j)
{
	if ((*lst)->next->type == 6)
		if_next_is_space(lst, splitting, lor_int, &j);
	else
		if_next_not_space(lst, lor_int, splitting, &j);
}

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
			cheack_if_space_or_not(lst, splitting, lor_int, j);
		}
		else
			if_next_is_null(lst, splitting, lor_int, &j);
	}
	else if (*lst != NULL && (*lst)->type == 3)
		chen = opening_rederections(lst, lor_int, chen, i);
	if (*lst)
	{
		lor_int->val = (*lst)->value;
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

void	init2(t_int *lor_int)
{
	lor_int->str = zyalloc(sizeof(char *) * 100);
	lor_int->out = 1;
	lor_int->in = 0;
	lor_int->fd = 0;
	lor_int->z = 0;
	lor_int->k = 0;
}

void	imbigious_red(t_int *lor_int, t_env *environment, char *var)
{
	if (lor_int->k == 20)
	{
		var = ft_get_env1(lor_int->val, environment);
		var = new_var_woutequal(var);
		var = ft_strjoin("$", var);
		printf("bash : %s:is an ambigious redirect\n", var);
	}
	return ;
}

void	creating_list(t_stack **lst, t_int *lor_int, t_env *environment)
{
	char	*var;

	init2(lor_int);
	while (*lst != NULL && ft_strcmp((*lst)->value, "|") != 0)
	{
		lor_int->val = NULL;
		var = NULL;
		lor_int->chen = NULL;
		lor_int->chen = rederection_handling(lst, lor_int, lor_int->chen);
		if (lor_int->k == 20 || lor_int->k == 30)
		{
			imbigious_red(lor_int, environment, var);
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

t_hxh	*ft_store(t_stack *lol, t_env *environment)
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
		creating_list(&lst, lor_int, environment);
		lor_int->str[lor_int->z] = NULL;
		ft_lstadd_back1(&l, ft_lstnew1(lor_int, lor_int->chen));
		if (lst == NULL)
			break ;
		increment_to_pipe(&lst);
	}
	return (l);
}
