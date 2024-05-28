/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:42 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/28 19:36:47 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *herdog_delm(t_stack **lst)
{
	t_stack    *tmp;
	char *str;

	tmp = *lst;
	str = NULL;
	while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
	{
		if (ft_strcmp(tmp->value, "<<") == 0)
		{
			if (tmp->next->type == 6)
			{
				tmp = tmp->next->next;
				if (tmp->next != NULL)
				{
					if (tmp->next->type != 6)
					{
						while (tmp->next != NULL)
						{
							if (tmp->next->type != 6)
							{
								if(!str)
									str = ft_strjoin(tmp->value , tmp->next->value);
								else 
									str = ft_strjoin(str , tmp->next->value);
							}
							else
								break ;
							tmp = tmp->next;
							*lst = tmp;
						}
					}
					else
					{
						str = tmp->value;
						*lst = tmp;
					}
				}
				else
				{
					str = tmp->value;
					*lst = tmp;
					// printf("%s\n", (*lst)->value);
				}
			}
			else if (tmp->next->type != 6)
			{
				tmp = tmp->next;
				if (tmp->next != NULL)
				{
					printf("ss--\n");
					if (tmp->next->type != 6)
					{
						while (tmp->next != NULL)
						{
							if (tmp->next->type != 6)
							{
								if(!str)
									str = ft_strjoin(tmp->value , tmp->next->value);
								else 
									str = ft_strjoin(str , tmp->next->value);
							}
							else
								break ;
							tmp = tmp->next;
							*lst = tmp;
						}
					}
					else
					{
						str = tmp->value;
						*lst = tmp;
					}
				}
				else
				{
					str = tmp->value;
					*lst = tmp;
					// printf("%s\n", (*lst)->value);
				}
			}
		}
		tmp = tmp->next;
	}
	return (str);
}
int	count_word(char *s)
{
	int	i;
	int	j;

	if (!s)
		return (0);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

int		more_than_two(t_stack *lst)
{
	int i;

	i = 0;
	lst = lst->next;
	while (lst)
	{
		if (i == 2)
			return (1);
		if (lst->type == 6)	
			i++;
		if (lst->type != 6)
			return(0);
		lst = lst->next;
	}
	return(0);
}

void	reder_open_file(t_stack **lst, t_int *lor_int, int *i)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next->next == NULL || more_than_two(*lst) || (*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		lor_int->fd = 1;
		*i = 2;
		return ;
	}
	else if (count_strings((*lst)->next->next->value, ' ') >= 2)
	{
		if ((*lst)->next->next->type == 2 || (*lst)->next->next->type == 1)
			*i = 0;
		else
		{
			lor_int->fd = 1;
			*i = 1;
			return ;
		}
	}
	lor_int->fd = open((*lst)->next->next->value,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	reder_open_file2(t_stack **lst, t_int *lor_int, int *i)
{
	if (lor_int->out >= 3)
		close(lor_int->fd);
	if ((*lst)->next == NULL || (*lst)->prev_is_null == 20 || (*lst)->next->prev_is_null == 20)
	{
		lor_int->fd = 1;
		*i = 2;
		return ;
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
			return ;
		}
	}
	lor_int->fd = open((*lst)->next->value, O_CREAT | O_RDWR | O_TRUNC,
			0644);
}

void	rederection(t_stack **lst, t_int *lor_int, int *i)
{
	if (ft_strcmp((*lst)->value, ">") == 0)
	{
		if ((*lst)->next)
		{
			if ((*lst)->next->type == 6)
				reder_open_file(lst, lor_int, i);
			else
				reder_open_file2(lst, lor_int, i);
		}
		else
			reder_open_file2(lst, lor_int, i);
		lor_int->out = lor_int->fd;
		if ((*lst)->next)
		{
			if ((*lst)->next->type == 6)
				(*lst) = (*lst)->next->next;
			else
				(*lst) = (*lst)->next;
		}
		else
			(*lst) = (*lst)->next;
	}
}
