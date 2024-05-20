/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:32:00 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/20 18:05:49 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*herdog_delm(t_stack *lst)
{
	t_stack	*tmp;

	tmp = lst;
	while (tmp != NULL && ft_strcmp(tmp->value, "|") != 0)
	{
		if (ft_strcmp(tmp->value, "<<") == 0)
		{
			if (tmp->next->type == 6)
				return (tmp->next->next->value);
			return (tmp->next->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int count_word(char *s)
{
	int i;
	int j;

	if(!s)
		return(0);
	j = 0;
	i = 0;
	while(s[i])
	{
		if(s[i] == ' ')
			j++;	
		i++;
	}
	return(j);
}

void rederection(t_stack **lst, int *in, int *out, int *fd, int *i)
{
	if (ft_strcmp((*lst)->value, ">") == 0)
	{
		if ((*lst)->next->type == 6)
		{
			if (*out >= 3)
				close(*fd);
			if(count_word((*lst)->next->next->value) >= 1)
			{
				*i = 1;
				return ;
			}
			*fd = open((*lst)->next->next->value, O_CREAT | O_RDWR, 0644);
		}
		else
		{
			if (*out >= 3)
				close(*fd);
			if(count_word((*lst)->next->value) >= 1)
			{
				*i = 1;
				return ;
			}
			*fd = open((*lst)->next->value, O_CREAT | O_RDWR, 0644);
		}
		*out = *fd;
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
	}
}

char	*infile(t_stack **lst, int *fd, int *in, int *out, int *i)
{
	char	*chen;

	chen = NULL;
	if (ft_strcmp((*lst)->value, "<") == 0)
	{
		if ((*lst)->next->type == 6)
		{
			if (access((*lst)->next->next->value, F_OK) == 0)
			{
				if (*in >= 3)
					close(*fd);
				if(count_word((*lst)->next->next->value) >= 1)
				{	
					*i = 1;
					return(NULL);
				}
				*fd = open((*lst)->next->next->value, O_RDWR, 0644);
				*in = *fd;
			}
			else
				chen = "No such file or directory";
		}
		else
		{
			if (access((*lst)->next->value, F_OK) == 0)
			{
				if (*in >= 3)
					close(*fd);
				if(count_word((*lst)->next->value) >= 1)
				{	
					*i = 1;
					return(NULL);
				}
				*fd = open((*lst)->next->value, O_RDWR, 0644);
				*in = *fd;
			}
			else
				chen = "No such file or directory";
		}
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
	}
	return (chen);
}

void	herdog(t_stack **lst, int *fd, t_int *lor_int, int *n, int *i)
{
	char	*ll;

	ll = NULL;
	if (ft_strcmp((*lst)->value, "<<") == 0)
	{
		lor_int->ten = ft_strjoin("file", ft_itoa(*n));
		if (lor_int->in >= 3)
			close(*fd);
		*fd = open(lor_int->ten, O_CREAT | O_RDWR | O_TRUNC, 0644);
		while (1)
		{
			ll = readline (">");
			if (!ll)
				exit(1);
			lor_int->zz = herdog_delm(*lst);
			if (ft_strcmp(lor_int->zz, ll) == 0)
				break ;
			ft_putstr_fd(ll, *fd);
			free(ll);
		}
		(*n)++;
		lor_int->in = *fd;
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
	}
}

void	append(t_stack **lst, int *fd, t_int *lor_int, int *i)
{
	if (ft_strcmp((*lst)->value, ">>") == 0)
	{
		if ((*lst)->next->type == 6)
		{
			if (lor_int->out >= 3)
				close(*fd);
			if(count_word((*lst)->next->next->value) >= 1)
			{
				*i = 1;
				return ;
			}
			*fd = open((*lst)->next->next->value, O_CREAT | O_RDWR | O_APPEND,
					0644);
		}
		else
		{
			if (lor_int->out >= 3)
				close(*fd);
			if(count_word((*lst)->next->value) >= 1)
			{
				*i = 1;
				return ;
			}
			*fd = open((*lst)->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		lor_int->out = *fd;
		if ((*lst)->next->type == 6)
			(*lst) = (*lst)->next->next;
		else
			(*lst) = (*lst)->next;
	}
}
