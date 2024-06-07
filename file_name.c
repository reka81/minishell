/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:22 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/07 17:40:29 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *file_name(t_stack **lst)
{
    char    *str;
    t_stack    *tmp;

    str = NULL;
    if ((*lst)->next->type == 6)
        tmp = (*lst)->next->next;
    else
        tmp = (*lst)->next;
    if (tmp->next != NULL)
    {
        while (tmp->next != NULL)
        {
            printf("ss----\n");
            if (tmp->next->type != 6)
            {
                if (tmp->next->type != 3)
                {
                    if (!str)
                        str = ft_strjoin(tmp->value, tmp->next->value);
                    else
                        str = ft_strjoin(str, tmp->next->value);
                }
                else
                {
                    str = tmp->value;
                    *lst = tmp;
                    break ;
                }
            }
            else
            {
                (1) && (str = tmp->value, *lst = tmp);
                break ;
            }
            tmp = tmp->next;
            *lst = tmp;
        }
    }
    else
    {
        str = tmp->value;
        *lst = tmp;
    }
    return (str);
}
