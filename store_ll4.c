/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:30:19 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/16 22:40:08 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hxh	*ft_lstnew1(char **content, int out, int in, char *str)
{
	t_hxh	*new_node;

	new_node = malloc(sizeof(t_hxh));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	if(str != NULL)
		new_node->is_faulty = 2;
	else
		new_node->is_faulty = 0;	
	new_node->output = out;
	new_node->input = in;
	new_node->next = NULL;
	return (new_node);
}

t_hxh	*ft_lstlast1(t_hxh *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back1(t_hxh **lst, t_hxh *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast1(*lst)->next = new;
	else
		*lst = new;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
