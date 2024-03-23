/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:49:35 by mettalbi          #+#    #+#             */
/*   Updated: 2024/03/23 08:29:32 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*ft_lstnew(char *content, int quote_type)
{
	t_stack	*s1;

	s1 = (t_stack *)malloc(sizeof(t_stack));
	if (!s1)
		return (NULL);
	s1->value = content;
	s1->type = quote_type;
	s1->next = NULL;
	return (s1);
}
