/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:30:20 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/20 16:45:00 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew2(void *variable, void *value)
{
	t_env	*s1;

	s1 = zyalloc(sizeof(t_env));
	if (!s1)
		return (NULL);
	s1->variable = variable;
	s1->value = value;
	s1->next = NULL;
	return (s1);
}
