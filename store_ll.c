/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:26:44 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/11 21:33:47 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	write(fd, "\n", 1);
}

int num_herdog(t_stack *lol)
{
	t_stack *tmp = lol;
	int count = 0;
	while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
	{
		if (ft_strcmp(tmp->value, "<<") == 0)
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}

char *rederection_handling(t_stack **lst, int n, t_int *lor_int, char *chen)
{
	if ((*lst) != NULL && ((*lst)->type == 1 || (*lst)->type == 2))
	{
		if((*lst)->next)
		{
			if ((*lst)->next->type == 6)
			{
				lor_int->str[lor_int->z] = (*lst)->value;
				lor_int->z++;
			}
			else
			{
				lor_int->str[lor_int->z] = ft_strjoin((*lst)->value, (*lst)->next->value);
				lor_int->z++;
				(*lst) = (*lst)->next;
			}
		}
		else
		{
			lor_int->str[lor_int->z] = (*lst)->value;
			lor_int->z++;
		}
	}
	else if (*lst != NULL && (*lst)->type == 0)
	{
		lor_int->str[lor_int->z] = (*lst)->value;
		lor_int->z++;
	}
	else if (*lst != NULL && (*lst)->type == 3)
	{
		rederection(lst, &lor_int->in, &lor_int->out, &lor_int->fd);
		chen = infile(lst, &lor_int->fd, &lor_int->in, &lor_int->out);
		herdog(lst , &lor_int->fd, lor_int, &n);
		append(lst, &lor_int->fd, lor_int);
	}
	return(chen);
}

t_hxh *ft_store(t_stack *lol)
{
	t_hxh *l;
	char *ll;
	int i = 0;
	t_int *lor_int = malloc(sizeof(t_int));
	int n = 1;
	char *chen = NULL;
	t_stack *lst;

	i = 0;
	n = 1;
	chen = NULL;
	lst = lol;
	l = NULL;
	lor_int = malloc(sizeof(t_int));
	while (lst != NULL)
	{
		lor_int->str = malloc(sizeof(char *) * 100);
		lor_int->out = 1;
		lor_int->in = 0;
		lor_int->fd = 0;
		lor_int->z = 0;
		while (lst != NULL && ft_strcmp(lst->value, "|") != 0)
		{
			chen = rederection_handling(&lst, n, lor_int, chen);
			lst = lst->next;
			if(lst == NULL)
				break;
		}
		lor_int->str[lor_int->z] = NULL;
		ft_lstadd_back1(&l, ft_lstnew1(lor_int->str, lor_int->out, lor_int->in));
		if(lst == NULL)
			break;
		lst = lst->next;
	}
	if (chen != NULL)
		printf("%s\n",chen);
	return (l);
}
