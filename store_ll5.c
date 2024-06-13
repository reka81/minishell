/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:08:24 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/13 17:11:21 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_herdog(t_stack *lol)
{
	t_stack	*tmp;
	int		count;

	count = 0;
	tmp = lol;
	while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
	{
		if (ft_strcmp(tmp->value, "<<") == 0)
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}

void	if_next_is_space(t_stack **lst, char **splitting,
	t_int *lor_int, int *j)
{
	if ((*lst)->did_expand == 40 && (*lst)->type != 1)
	{
		splitting = ft_split((*lst)->value, ' ');
		while (splitting[*j])
		{
			lor_int->str[lor_int->z] = splitting[*j];
			(*j)++;
			lor_int->z++;
		}
	}
	else
	{
		lor_int->str[lor_int->z] = (*lst)->value;
		lor_int->z++;
	}
}

void	split_or_not_split(t_stack **lst, char **splitting,
	t_int *lor_int, int *j)
{
	if ((*lst)->did_expand == 40)
	{
		if ((*lst)->type == 0)
		{
			splitting = ft_split((*lst)->value, ' ');
			while (splitting[*j])
			{
				lor_int->str[lor_int->z] = splitting[*j];
				(*j)++;
				lor_int->z++;
			}
			*j = 0;
		}
		else if ((*lst)->type == 1)
		{
			lor_int->str[lor_int->z] = (*lst)->value;
			lor_int->z++;
		}
	}
	else
	{
		lor_int->str[lor_int->z] = (*lst)->value;
		lor_int->z++;
	}
}

void	handling_space_in_expanding(t_stack **lst, char **splitting,
	int *j, t_int *lor_int)
{
	if ((*lst)->next->value[0] != ' ')
	{
		splitting = ft_split((*lst)->next->value, ' ');
		while (splitting[*j])
		{
			if ((*j) == 0)
				lor_int->str[lor_int->z - 1] = ft_strjoin(lor_int
						->str[lor_int->z - 1], (*lst)->next->value);
			else
			{
				lor_int->str[lor_int->z] = splitting[*j];
				lor_int->z++;
			}
			(*j)++;
		}
	}
	else
	{
		splitting = ft_split((*lst)->next->value, ' ');
		while (splitting[*j])
		{
			lor_int->str[lor_int->z] = splitting[*j];
			(*j)++;
			lor_int->z++;
		}
	}
	*j = 0;
}

void	handling_dq(t_stack **lst, char **splitting, int *j, t_int *lor_int)
{
	if ((*lst)->did_expand == 40 && (*lst)->type != 1)
	{
		splitting = ft_split((*lst)->value, ' ');
		while (splitting[*j])
		{
			lor_int->str[lor_int->z] = splitting[*j];
			(*j)++;
			lor_int->z++;
		}
	}
	else
	{
		lor_int->str[lor_int->z] = (*lst)->value;
		lor_int->z++;
	}
}
