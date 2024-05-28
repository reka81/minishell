/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:08:24 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/28 20:31:23 by mettalbi         ###   ########.fr       */
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

void	if_next_not_space(t_stack **lst, t_int *lor_int, char **splitting, int *j)
{
	if((*lst)->next->type != 3)
	{
		// lor_int->str[lor_int->z] = ft_strjoin((*lst)->value,
		// 		(*lst)->next->value);
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
				j = 0;
			}
			else if((*lst)->type == 1)
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
		if ((*lst)->next->did_expand == 40)
		{
			if ((*lst)->next->type == 1)
			{
				lor_int->str[lor_int->z - 1] = ft_strjoin(lor_int->str[lor_int->z - 1], (*lst)->next->value);
			}
			else if ((*lst)->next->type == 0)
			{
				if ((*lst)->next->value[0] != ' ')
				{
					splitting = ft_split((*lst)->next->value, ' ');
					while (splitting[*j])
					{
						if ((*j) == 0)
						{
							lor_int->str[lor_int->z - 1] = ft_strjoin(lor_int->str[lor_int->z - 1], (*lst)->next->value);
						}
						else
							lor_int->str[lor_int->z] = splitting[*j];
						(*j)++;
						lor_int->z++;
					}
					j = 0;
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
					j = 0;
				}
			}
		}
		else
			lor_int->str[lor_int->z - 1] = ft_strjoin(lor_int->str[lor_int->z - 1], (*lst)->next->value);
		(*lst) = (*lst)->next;
	}
	else
	{
		if ((*lst)->did_expand == 40 && (*lst)->type != 1)
		{
			splitting = ft_split((*lst)->value , ' ');
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
}


void	if_next_is_null(t_stack **lst, char **splitting, t_int *lor_int, int *j)
{
	if ((*lst)->did_expand == 40 && (*lst)->type != 1)
	{
		splitting = ft_split((*lst)->value, ' ');
		while (splitting[*j])
		{
			lor_int->str[lor_int->z] = splitting[*j];
			lor_int->z++;
			(*j)++;
		}
	}
	else
	{
		lor_int->str[lor_int->z] = (*lst)->value;
		lor_int->z++;
	}
}

char	*opening_rederections(t_stack **lst, t_int *lor_int, char *chen, int i)
{
	extern int	g_is_in_mini;

	rederection(lst, lor_int, &i);
	if (i == 1 || i == 2)
	{
		if (i == 1)
			lor_int->k = 20;
		else
			lor_int->k = 30;
		return (chen);
	}
	chen = infile(lst, lor_int, &i);
	if (i == 1 || i == 2)
	{
		if (i == 1)
			lor_int->k = 20;
		else
			lor_int->k = 30;
		return (chen);
	}
	g_is_in_mini = 2;
	if (read(0, NULL, 0) == -1)
	{
		chen = "broken";
		return (chen);
	}
	herdog(lst, lor_int);
	g_is_in_mini = 0;
	append(lst, &lor_int->fd, lor_int, &i);
	if (i == 1 || i == 2)
	{
		if (i == 1)
			lor_int->k = 20;
		else
			lor_int->k = 30;
		return (chen);
	}
	return (chen);
}
