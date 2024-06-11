/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:31 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/11 14:09:19 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*infile_chen(t_stack **lst, t_int *lor_int, char *chen)
{
	char	*str;

	str = file_name(lst);
	if (access(str, F_OK) == 0)
	{
		if (lor_int->in >= 3)
			close(lor_int->fd);
		lor_int->fd = open(str, O_RDWR, 0644);
		lor_int->in = lor_int->fd;
		if (lor_int->fd < 0)
		{
			ft_putstr_fd2("bash: ", 2);
			ft_putstr_fd2(str, 2);
			ft_putstr_fd2(": Permission denied\n", 2);
			chen = "invalid";
		}
	}
	else
		chen = "No such file or directory";
	return (chen);
}

char	*infile_chen2(t_stack **lst, t_int *lor_int, char *chen)
{
	char	*str;

	str = file_name(lst);
	if (access(str, F_OK) == 0)
	{
		if (lor_int->in >= 3)
			close(lor_int->fd);
		lor_int->fd = open(str, O_RDWR, 0644);
		lor_int->in = lor_int->fd;
		if (lor_int->fd < 0)
		{
			ft_putstr_fd2("bash: ", 2);
			ft_putstr_fd2(str, 2);
			ft_putstr_fd2(": Permission denied\n", 2);
			chen = "invalid";
		}
	}
	else
		chen = "No such file or directory";
	return (chen);
}

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
	chen = infile_chen(lst, lor_int, chen);
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
	chen = infile_chen2(lst, lor_int, chen);
	return (chen);
}

char	*infile(t_stack **lst, t_int *lor_int, int *i, char *chen)
{
	if (ft_strcmp((*lst)->value, "<") == 0)
	{
		if ((*lst)->next->type == 6)
			chen = infile_open_file(lst, chen, i, lor_int);
		else
		{
			chen = infile_open_file1(lst, chen, i, lor_int);
		}
	}
	return (chen);
}
