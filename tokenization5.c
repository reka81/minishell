/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:15:02 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/31 15:01:40 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rm_null2(t_stack **a, t_stack *tmp1, t_stack *tmp)
{
	tmp1 = (*a)->next;
	(*a) = tmp;
	(*a)->next = tmp1;
	(*a)->prev_is_null = 20;
}

void	first_value_null(t_stack **a, t_stack **tmp2)
{
	*tmp2 = (*a)->next;
	(*a) = *tmp2;
	if (*a)
		(*a)->prev_is_null = 20;
}

void	ft_rm_null(t_stack **a)
{
	int			i;
	t_stack		*tmp1;
	t_stack		*tmp2;
	t_stack		*tmp;

	i = 0;
	tmp2 = *a;
	tmp1 = NULL;
	while ((*a) != NULL)
	{
		if ((*a)->value == NULL && i == 0)
			first_value_null(a, &tmp2);
		else if ((*a)->value == NULL && (*a)->next != NULL)
			ft_rm_null2(a, tmp1, tmp);
		else if ((*a)->value == NULL && (*a)->next == NULL)
		{
			tmp->next = NULL;
			(*a)->prev_is_null = 20;
		}
		tmp = *a;
		if (*a)
			*a = (*a)->next;
		i++;
	}
	*a = tmp2;
}

void	init(t_numbers *tokens)
{
	tokens->i = 0;
	tokens->j = 0;
	tokens->quote_flag = 0;
	tokens->flag_for_white = 0;
}

void	rest_of_tokenization(char *str, t_numbers *tokens, t_stack **a, char *l)
{
	if (tokens->flag_for_white)
	{
		if (tokens->quote_flag == 0 && str[0] == '\0')
			return ;
		ft_lstadd_back(a, ft_lstnew(str, tokens->quote_flag));
		tokens->quote_flag = 0;
		tokens->flag_for_white = 0;
	}
	if (l[tokens->i] == '|')
	{
		ft_lstadd_back(a, ft_lstnew(strdup("|"), 3));
		tokens->i++;
	}
	if (l[tokens->i] == ' ')
	{
		ft_lstadd_back(a, ft_lstnew(strdup(" "), 6));
		while (l[tokens->i] == ' ')
			tokens->i++;
	}
}
