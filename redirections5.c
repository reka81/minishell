/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:03:52 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:04:41 by mettalbi         ###   ########.fr       */
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

char	*str_setting(t_stack **tmp, char *str)
{
	if (!str)
		str = ft_strjoin((*tmp)->value, (*tmp)->next->value);
	else
		str = ft_strjoin(str, (*tmp)->next->value);
	return (str);
}
