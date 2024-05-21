/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:32:00 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/21 16:07:20 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_lst(t_stack **lst)
{
	if ((*lst)->next->type == 6)
		(*lst) = (*lst)->next->next;
	else
		(*lst) = (*lst)->next;
}

void	herdog(t_stack **lst, t_int *lor_int, int *i)
{
	char	*ll;

	ll = NULL;
	if (ft_strcmp((*lst)->value, "<<") == 0)
	{
		lor_int->ten = ft_strjoin("file", ft_itoa(lor_int->n));
		if (lor_int->in >= 3)
			close(lor_int->fd);
		lor_int->fd = open(lor_int->ten, O_CREAT | O_RDWR | O_TRUNC, 0644);
		while (1)
		{
			ll = readline (">");
			if (!ll)
				exit(1);
			lor_int->zz = herdog_delm(*lst);
			if (ft_strcmp(lor_int->zz, ll) == 0)
				break ;
			ft_putstr_fd(ll, lor_int->fd);
			free(ll);
		}
		lor_int->n++;
		lor_int->in = lor_int->fd;
	}
}

void	append_open_file(t_stack **lst, int *fd, int *i, t_int *lor_int)
{
	if (lor_int->out >= 3)
		close(*fd);
	if (count_word((*lst)->next->next->value) >= 1)
	{
		*i = 1;
		return ;
	}
	*fd = open((*lst)->next->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
}

void	append(t_stack **lst, int *fd, t_int *lor_int, int *i)
{
	if (ft_strcmp((*lst)->value, ">>") == 0)
	{
		if ((*lst)->next->type == 6)
			append_open_file(lst, fd, i, lor_int);
		else
		{
			if (lor_int->out >= 3)
				close(*fd);
			if (count_word((*lst)->next->value) >= 1)
			{
				*i = 1;
				return ;
			}
			*fd = open((*lst)->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		lor_int->out = *fd;
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
	}
}
