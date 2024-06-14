/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:26:44 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/14 17:32:16 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init2(t_int *lor_int, t_stack *lst)
{
	lor_int->str = zyalloc(sizeof(char *) * (ft_lstsize2(lst) + 2));
	lor_int->str[0] = NULL;
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

void	creating_list(t_stack **lst, t_int *lor_int,
	t_env *environment, int *last_pipe)
{
	char	*var;

	lor_int->env = environment;
	init2(lor_int, *lst);
	while (*lst != NULL && (ft_strcmp((*lst)->value, "|") != 0
			|| (*lst)->type != 3))
	{
		initing_values(lor_int, &var, lst);
		if (lor_int->k == 20 || lor_int->k == 30)
		{
			imbigious_red(lor_int, environment, var);
			break ;
		}
		if (lor_int->chen != NULL)
		{
			if (ft_strcmp("broken", lor_int->chen) == 0
				|| ft_strcmp("invalid", lor_int->chen) == 0)
				break ;
			(ft_putstr_fd2(lor_int->chen, 2), ft_putstr_fd2("\n", 2));
			break ;
		}
		if (*lst == NULL)
			break ;
		last_pipe_num(lst, last_pipe);
	}
}

t_hxh	*ft_store(t_stack *lol, t_env *environment, int *exit_status)
{
	t_hxh	*l;
	t_int	*lor_int;
	t_stack	*lst;
	int		last_pipe;

	lst = lol;
	l = NULL;
	lor_int = zyalloc(sizeof(t_int));
	lor_int->i = 0;
	lor_int->n = 1;
	lor_int->chen = NULL;
	(1) && (lor_int->exit_status = exit_status, last_pipe = 0);
	while (lst != NULL)
	{
		creating_list(&lst, lor_int, environment, &last_pipe);
		lor_int->str[lor_int->z] = NULL;
		ft_lstadd_back1(&l, ft_lstnew1(lor_int, lor_int->chen));
		if (last_pipe == 1)
			(init2(lor_int, lol),
				ft_lstadd_back1(&l, ft_lstnew1(lor_int, lor_int->chen)));
		if (lst == NULL)
			break ;
		increment_to_pipe(&lst);
	}
	return (l);
}
