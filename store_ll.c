/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:26:44 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/16 22:52:42 by mettalbi         ###   ########.fr       */
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

int	num_herdog(t_stack *lol)
{
	t_stack	*tmp;
	int		count;

	count = 0;
	tmp = lol;
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

char	*rederection_handling(t_stack **lst, int n, t_int *lor_int, char *chen)
{
	if ((*lst) != NULL && ((*lst)->type == 1 || (*lst)->type == 2 || (*lst)->type == 0))
	{
		if ((*lst)->next)
		{
			if ((*lst)->next->type == 6)
			{
				lor_int->str[lor_int->z] = (*lst)->value;
				lor_int->z++;
			}
			else
			{
				lor_int->str[lor_int->z] = ft_strjoin((*lst)->value,
						(*lst)->next->value);
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
	else if (*lst != NULL && (*lst)->type == 3)
	{
		rederection(lst, &lor_int->in, &lor_int->out, &lor_int->fd);
		chen = infile(lst, &lor_int->fd, &lor_int->in, &lor_int->out);
		herdog(lst, &lor_int->fd, lor_int, &n);
		append(lst, &lor_int->fd, lor_int);
	}
	return (chen);
}

t_hxh	*ft_store(t_stack *lol)
{
	t_hxh	*l;
	t_int	*lor_int;
	t_stack	*lst;
	t_store	*storing;

	storing = malloc(sizeof(t_store));
	storing->i = 0;
	storing->n = 1;
	storing->chen = NULL;
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
			storing->chen = NULL;
			storing->chen = rederection_handling(&lst, storing->n,
					lor_int, storing->chen);
			lst = lst->next;
			if (storing->chen != NULL)
			{
				printf("%s\n", storing->chen);
				break;
			}
			if (lst == NULL)
				break ;
		}
		lor_int->str[lor_int->z] = NULL;
		ft_lstadd_back1(&l, ft_lstnew1(lor_int->str,
				lor_int->out, lor_int->in, storing->chen));
		if (lst == NULL)
			break ;
		if(lst &&  ft_strcmp(lst->value, "|") != 0)
		{    
			while(lst &&  ft_strcmp(lst->value, "|") != 0)
				lst = lst->next;
			if(ft_strcmp(lst->value, "|") == 0)
				lst = lst->next;
        }
        else
            lst = lst->next;
	}
	return (l);
}
