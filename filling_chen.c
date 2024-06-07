/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_chen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:18:49 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:24:33 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_chen(t_stack **lst, t_int *lor_int, char *chen)
{
	char	*str;

	str = file_name(lst);
	lor_int->fd = open(str,
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (lor_int->fd < 0)
	{
		ft_putstr_fd2("bash: ", 2);
		ft_putstr_fd2(str, 2);
		ft_putstr_fd2(": Permission denied\n", 2);
		chen = "invalid";
	}
	return (chen);
}

char	*append_chen2(t_stack **lst, t_int *lor_int, char *chen)
{
	char	*str;

	str = file_name(lst);
	lor_int->fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (lor_int->fd < 0)
	{
		ft_putstr_fd2("bash: ", 2);
		ft_putstr_fd2(str, 2);
		ft_putstr_fd2(": Permission denied\n", 2);
		chen = "invalid";
	}
	return (chen);
}

char	*reder_chen(t_stack **lst, t_int *lor_int, char *chen)
{
	char	*str;

	str = file_name(lst);
	lor_int->fd = open(str,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (lor_int->fd < 0)
	{
		ft_putstr_fd2("bash: ", 2);
		ft_putstr_fd2(str, 2);
		ft_putstr_fd2(": Permission denied\n", 2);
		chen = "invalid";
	}
	return (chen);
}

char	*reder_chen2(t_stack **lst, t_int *lor_int, char *chen)
{
	char	*str;

	str = file_name(lst);
	lor_int->fd = open(str, O_CREAT | O_RDWR | O_TRUNC,
			0644);
	if (lor_int->fd < 0)
	{
		ft_putstr_fd2("bash: ", 2);
		ft_putstr_fd2(str, 2);
		ft_putstr_fd2(": Permission denied\n", 2);
		chen = "invalid";
	}
	return (chen);
}

void	last_pipe_num(t_stack **lst, int *last_pipe)
{
	if (ft_strcmp((*lst)->value, "|") == 0 && (*lst)->next == NULL)
		*last_pipe = 1;
	else
		*last_pipe = 0;
}
