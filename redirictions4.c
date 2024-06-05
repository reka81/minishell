/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:33:35 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/05 19:28:04 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cheack_if_space_or_not(t_stack **lst, char **splitting,
		t_int *lor_int, int j)
{
	if ((*lst)->next->type == 6)
		if_next_is_space(lst, splitting, lor_int, &j);
	else
		if_next_not_space(lst, lor_int, splitting, &j);
}

char	*rederection_handling(t_stack **lst, t_int *lor_int, char *chen)
{
	int			i;
	char		**splitting;
	int			j;

	i = 0;
	j = 0;
	splitting = NULL;
	if ((*lst) != NULL && ((*lst)->type == 1
			|| (*lst)->type == 2 || (*lst)->type == 0))
	{
		if ((*lst)->next)
			cheack_if_space_or_not(lst, splitting, lor_int, j);
		else
			if_next_is_null(lst, splitting, lor_int, &j);
	}
	else if (*lst != NULL && (*lst)->type == 3)
		chen = opening_rederections(lst, lor_int, chen, i);
	if (*lst)
	{
		lor_int->val = (*lst)->value;
		(*lst) = (*lst)->next;
	}
	return (chen);
}

char    *append(t_stack **lst, t_int *lor_int, int *i, char *chen)
{
    if (ft_strcmp((*lst)->value, ">>") == 0)
    {
        if ((*lst)->next->type == 6)
            chen = append_open_file(lst, i, lor_int, chen);
        else
            chen = append_open_file2(lst, i, lor_int, chen);
        lor_int->out = lor_int->fd;
        if ((*lst)->next->type == 6)
            (*lst) = (*lst)->next->next;
        else
            (*lst) = (*lst)->next;
    }
    return (chen);
}
