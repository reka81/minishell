/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:32:00 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/23 16:03:19 by mettalbi         ###   ########.fr       */
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

void	herdog(t_stack **lst, t_int *lor_int)
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
				break ;
			lor_int->zz = herdog_delm(*lst);
			if (ft_strcmp(lor_int->zz, ll) == 0)
				break ;
			(ft_putstr_fd(ll, lor_int->fd), free(ll));
		}
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
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

void	append_open_file2(t_stack **lst, int *fd, int *i, t_int *lor_int)
{
	if (lor_int->out >= 3)
		close(*fd);
	if ((*lst)->next == NULL)
	{
		*i = 1;
		return ;
	}
	else if (count_strings((*lst)->next->value, ' ') >= 2)
	{
		if ((*lst)->next->type == 2 || (*lst)->next->type == 1)
			*i = 0;
		else
		{
			*i = 1;
			return ;
		}
	}
	*fd = open((*lst)->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
}

void	append(t_stack **lst, int *fd, t_int *lor_int, int *i)
{
	if (ft_strcmp((*lst)->value, ">>") == 0)
	{
		if ((*lst)->next->type == 6)
			append_open_file(lst, fd, i, lor_int);
		else
			append_open_file2(lst, fd, i, lor_int);
		lor_int->out = *fd;
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
	}
}
