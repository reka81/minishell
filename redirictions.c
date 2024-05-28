/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:32:00 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/28 19:48:09 by mettalbi         ###   ########.fr       */
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
	int		fd1;

	ll = NULL;
	if (ft_strcmp((*lst)->value, "<<") == 0)
	{
		lor_int->ten = ft_strjoin("file", ft_itoa(lor_int->n));
		if (lor_int->in >= 3)
			close(lor_int->fd);
		lor_int->fd = open(lor_int->ten, O_CREAT | O_RDWR | O_TRUNC, 0644);
		fd1 = open(lor_int->ten, O_RDWR);
		unlink(lor_int->ten);
		lor_int->zz = herdog_delm(lst);
		while (1)
		{
			ll = readline (">");
			if (!ll)
				break ;
			if (ft_strcmp(lor_int->zz, ll) == 0)
				break ;
			(ft_putstr_fd(ll, lor_int->fd), free(ll));
		}
		close(lor_int->fd);
		lor_int->fd = fd1;
		lor_int->n++;
		lor_int->in = lor_int->fd;
	}
}

void	append_open_file(t_stack **lst, int *fd, int *i, t_int *lor_int)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next->next == NULL || more_than_two(*lst) || (*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		lor_int->fd = 1;
		*i = 2;
		return ;
	}
	else if (count_strings((*lst)->next->next->value, ' ') >= 2)
	{
		if ((*lst)->next->next->type == 2 || (*lst)->next->next->type == 1)
			*i = 0;
		else
		{
			lor_int->fd = 1;
			*i = 1;
			return ;
		}
	}
	*fd = open((*lst)->next->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
}

void	append_open_file2(t_stack **lst, int *fd, int *i, t_int *lor_int)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next == NULL || (*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		lor_int->fd = 1;
		*i = 2;
		return ;
	}
	else if ((*lst)->next == NULL
		|| count_strings((*lst)->next->value, ' ') >= 2)
	{
		if ((*lst)->next->type == 2 || (*lst)->next->type == 1)
			*i = 0;
		else
		{
			lor_int->fd = 1;
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
