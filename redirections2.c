/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:31 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/30 21:39:49 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*infile_open_file(t_stack **lst, char *chen, int *i, t_int *lor_int)
{
	if ((*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		*i = 2;
		return (NULL);
	}
	else if (count_strings((*lst)->next->next->value, ' ') >= 2)
	{
		if ((*lst)->next->next->type == 2 || (*lst)->next->next->type == 1)
			*i = 0;
		else
		{
			*i = 1;
			return (NULL);
		}
	}
	if (access((*lst)->next->next->value, F_OK) == 0)
	{
		if (lor_int->in >= 3)
			close(lor_int->fd);
		lor_int->fd = open((*lst)->next->next->value, O_RDWR, 0644);
		lor_int->in = lor_int->fd;
	}
	else
		chen = "No such file or directory";
	return (chen);
}

char	*infile_open_file1(t_stack **lst, char *chen, int *i, t_int *lor_int)
{
	if ((*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		*i = 2;
		return (NULL);
	}
	else if (count_strings((*lst)->next->value, ' ') >= 2)
	{
		if ((*lst)->next->type == 2 || (*lst)->next->type == 1)
			*i = 0;
		else
		{
			return (NULL);
		}
	}
	if (access((*lst)->next->value, F_OK) == 0)
	{
		if (lor_int->in >= 3)
			close(lor_int->fd);
		lor_int->fd = open((*lst)->next->value, O_RDWR, 0644);
		lor_int->in = lor_int->fd;
	}
	else
		chen = "No such file or directory";
	return (chen);
}

char	*infile(t_stack **lst, t_int *lor_int, int *i)
{
	char	*chen;

	chen = NULL;
	if (ft_strcmp((*lst)->value, "<") == 0)
	{
		if ((*lst)->next->type == 6)
			chen = infile_open_file(lst, chen, i, lor_int);
		else
		{
			chen = infile_open_file1(lst, chen, i, lor_int);
		}
		if ((*lst)->next)
		{
			if ((*lst)->next->type == 6)
				(*lst) = (*lst)->next->next;
			else
				(*lst) = (*lst)->next;
		}
		else
			(*lst) = (*lst)->next;
	}
	return (chen);
}
