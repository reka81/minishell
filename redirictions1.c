/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:42 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/21 23:23:06 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*herdog_delm(t_stack *lst)
{
	t_stack	*tmp;

	tmp = lst;
	while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
	{
		if (ft_strcmp(tmp->value, "<<") == 0)
		{
			if (tmp->next->type == 6)
				return (tmp->next->next->value);
			return (tmp->next->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	count_word(char *s)
{
	int	i;
	int	j;

	if (!s)
		return (0);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

void	reder_open_file(t_stack **lst, t_int *lor_int, int *i)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next->next == NULL)
	{
		*i = 1;
		return ;
	}
	else if (count_strings((*lst)->next->next->value, ' ') >= 2)
	{
		if ((*lst)->next->next->type == 2 || (*lst)->next->next->type == 1)
			*i = 0;
		else
		{
			*i = 1;
			return ;
		}
	}
	lor_int->fd = open((*lst)->next->next->value,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	reder_open_file2(t_stack **lst, t_int *lor_int, int *i)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next == NULL)
	{
		*i = 1;
		return ;
	}
	else if ((*lst)->next == NULL
		|| count_strings((*lst)->next->value, ' ') >= 2)
	{
		if ((*lst)->next->type == 2 || (*lst)->next->type == 1)
			*i = 0;
		else
		{
			*i = 1;
			return ;
		}
	}
	lor_int->fd = open((*lst)->next->value, O_CREAT | O_RDWR | O_TRUNC,
			0644);
}

void	rederection(t_stack **lst, t_int *lor_int, int *i)
{
	if (ft_strcmp((*lst)->value, ">") == 0)
	{
		if ((*lst)->next->type == 6)
			reder_open_file(lst, lor_int, i);
		else
			reder_open_file2(lst, lor_int, i);
		lor_int->out = lor_int->fd;
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
	}
}
