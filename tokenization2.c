/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:05:27 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/24 19:47:13 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rest_of_tokenization2(t_numbers *tokens, char *str, char *l)
{
	tokens->i++;
	while (l[tokens->i] != '"')
	{
		str[tokens->j] = l[tokens->i];
		tokens->i++;
		tokens->j++;
	}
	tokens->quote_flag = 1;
	tokens->flag_for_white = 1;
	tokens->i++;
}

void	rest_of_tokenization3(char *l, t_numbers *tokens, char *str)
{
	while (l[tokens->i] != '\'')
	{
		str[tokens->j] = l[tokens->i];
		tokens->i++;
		tokens->j++;
	}
	tokens->quote_flag = 2;
	tokens->flag_for_white = 1;
}

void	rest_of_tokenization4(t_numbers *tokens, char *l, char *str)
{
	while (l[tokens->i] != '>' && l[tokens->i] != ' ' && l[tokens->i] != '<'
		&& l[tokens->i] && l[tokens->i] != '|')
	{
		if (l[tokens->i] == '"')
		{
			if (tokens->j > 0)
				break ;
			rest_of_tokenization2(tokens, str, l);
			break ;
		}
		if (l[tokens->i] == '\'')
		{
			if (tokens->j > 0)
				break ;
			tokens->i++;
			rest_of_tokenization3(l, tokens, str);
			tokens->i++;
			break ;
		}
		str[tokens->j] = l[tokens->i];
		tokens->j++;
		tokens->i++;
		tokens->flag_for_white = 1;
	}
}

void	rest_of_tokenization5(char *l, t_numbers *tokens
		, char *str, char *operator)
{
	while (l[tokens->i] == '>' || l[tokens->i] == '<')
	{
		operator = &l[tokens->i];
		str[tokens->j] = *operator;
		tokens->i++;
		tokens->j++;
	}
}

void	tokenization(t_stack **a, char *l)
{
	t_numbers	*tokens;
	char		*str;
	char		operator;

	tokens = zyalloc(sizeof(t_numbers));
	operator = 0;
	str = NULL;
	init(tokens);
	while (l[tokens->i])
	{
		tokens->j = 0;
		str = zyalloc(ft_strlen1(l) + 2);
		rest_of_tokenization4(tokens, l, str);
		str[tokens->j] = '\0';
		rest_of_tokenization(str, tokens, a, l);
		tokens->j = 0;
		if (l[tokens->i] == '>' || l[tokens->i] == '<')
		{
			str = zyalloc(ft_strlen1(l));
			rest_of_tokenization5(l, tokens, str, &operator);
			str[tokens->j] = '\0';
			ft_lstadd_back(a, ft_lstnew(str, 3));
		}
	}
}
