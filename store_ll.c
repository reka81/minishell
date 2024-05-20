/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:26:44 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/20 16:45:00 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char *)zyalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = ' ';
	i++;
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
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

char	*rederection_handling(t_stack **lst, int n, t_int *lor_int, char *chen, int *k)
{
	int i = 0;
	char **splitting;
	int j = 0;

	if ((*lst) != NULL && ((*lst)->type == 1 || (*lst)->type == 2 || (*lst)->type == 0))
	{
		if ((*lst)->next)
		{
			if ((*lst)->next->type == 6)
			{
				if((*lst)->did_expand == 40)
				{
					splitting = ft_split((*lst)->value, ' ');
					while(splitting[j])
					{
						lor_int->str[lor_int->z] = splitting[j];
						j++;
						lor_int->z++;
					}
				}
				else
				{
					lor_int->str[lor_int->z] = (*lst)->value;
					lor_int->z++;
				}
			}
			else
			{
				lor_int->str[lor_int->z] = ft_strjoin((*lst)->value,
						(*lst)->next->value);
				if((*lst)->did_expand == 40 || (*lst)->next->did_expand == 40)
				{
					lor_int->str = ft_split((lor_int)->str[lor_int->z], ' ');
					while(lor_int->str[lor_int->z])
						lor_int->z++;
				}
				else
					lor_int->z++;
				(*lst) = (*lst)->next;
			}
		}
		else
		{
			if((*lst)->did_expand == 40)
			{
				splitting = ft_split((*lst)->value, ' ');
				while(splitting[j])
				{
					lor_int->str[lor_int->z] = splitting[j];
					lor_int->z++;
					j++;
				}
			}
			else
			{
				lor_int->str[lor_int->z] = (*lst)->value;
				lor_int->z++;
			}
		}
	}
	else if (*lst != NULL && (*lst)->type == 3)
	{
		rederection(lst, &lor_int->in, &lor_int->out, &lor_int->fd, &i);
		if(i == 1)
		{	
			*k = 20;
			return(chen);
		}
		chen = infile(lst, &lor_int->fd, &lor_int->in, &lor_int->out, &i);
		if(i == 1)
		{
			*k = 20;
			return(chen);
		}
		herdog(lst, &lor_int->fd, lor_int, &n, &i);
		if(i == 1)
		{
			*k = 20;
			return(chen);
		}
		append(lst, &lor_int->fd, lor_int, &i);
		if(i == 1)
		{
			*k = 20;
			return(chen);
		}
	}
	return (chen);
}

t_hxh	*ft_store(t_stack *lol)
{
	t_hxh	*l;
	t_int	*lor_int;
	t_stack	*lst;
	t_store	*storing;
	int i;

	storing = zyalloc(sizeof(t_store));
	storing->i = 0;
	storing->n = 1;
	storing->chen = NULL;
	lst = lol;
	l = NULL;
	lor_int = zyalloc(sizeof(t_int));
	while (lst != NULL)
	{
		lor_int->str = zyalloc(sizeof(char *) * 100);
		lor_int->out = 1;
		lor_int->in = 0;
		lor_int->fd = 0;
		lor_int->z = 0;
		int i = 0;
		while (lst != NULL && ft_strcmp(lst->value, "|") != 0)
		{
			storing->chen = NULL;
			storing->chen = rederection_handling(&lst, storing->n,
					lor_int, storing->chen, &i);
			lst = lst->next;
			if(i == 20)
			{
				printf("is an ambigious redirect\n");
				break;
			}
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
				lor_int->out, lor_int->in, storing->chen, i));
		if (lst == NULL)
			break ;
		if(lst &&  ft_strcmp(lst->value, "|") != 0)
		{    
			while(lst &&  ft_strcmp(lst->value, "|") != 0)
				lst = lst->next;
			if(lst)
			{
				if(ft_strcmp(lst->value, "|") == 0)
					lst = lst->next;
			}
		}
        else
            lst = lst->next;
	}
	return (l);
}
