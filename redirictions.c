/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:32:00 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/13 15:31:03 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	herdog_v1(t_int *lor_int, int fd1)
{
	close(lor_int->fd);
	lor_int->fd = fd1;
	lor_int->n++;
	lor_int->in = lor_int->fd;
}

void	herdog_loop(char *ll, char *her, t_int *lor_int, int flag)
{
	while (1)
	{
		her = NULL;
		ll = readline (">");
		if (!ll)
			break ;
		if (ft_strcmp(lor_int->zz, ll) == 0)
		{
			free(ll);
			break ;
		}
		if (flag == 0)
			her = expanding_her(ll, *lor_int->exit_status, lor_int->env);
		if (!her)
			(ft_putstr_fd(ll, lor_int->fd), free(ll));
		else
			(ft_putstr_fd(her, lor_int->fd), free(ll));
	}
}

void	herdog(t_stack **lst, t_int *lor_int)
{
	char	*ll;
	int		fd1;
	char	*her;
	int		flag;

	flag = 0;
	ll = NULL;
	her = NULL;
	if (ft_strcmp((*lst)->value, "<<") == 0)
	{
		lor_int->ten = ft_strjoin("file", ft_itoa(lor_int->n));
		if (lor_int->in >= 3)
			close(lor_int->fd);
		lor_int->fd = open(lor_int->ten, O_CREAT | O_RDWR | O_TRUNC, 0644);
		fd1 = open(lor_int->ten, O_RDWR);
		unlink(lor_int->ten);
		lor_int->zz = herdog_delm(lst, &flag);
		herdog_loop(ll, her, lor_int, flag);
		herdog_v1(lor_int, fd1);
	}
}

char	*append_open_file(t_stack **lst, int *i, t_int *lor_int, char *chen)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next->next == NULL
		|| (*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		lor_int->fd = 1;
		*i = 2;
		return (NULL);
	}
	else if (count_strings((*lst)->next->next->value, ' ') >= 2)
	{
		if ((*lst)->next->next->type == 2 || (*lst)->next->next->type == 1)
			*i = 0;
		else
		{
			lor_int->fd = 1;
			*i = 1;
			return (NULL);
		}
	}
	chen = append_chen(lst, lor_int, chen);
	return (chen);
}

char	*append_open_file2(t_stack **lst, int *i, t_int *lor_int, char *chen)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next == NULL
		|| (*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		lor_int->fd = 1;
		*i = 2;
		return (NULL);
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
			return (NULL);
		}
	}
	chen = append_chen2(lst, lor_int, chen);
	return (chen);
}
