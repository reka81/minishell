/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:21:07 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/21 19:56:27 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_sq(char *str, int *i)
{
	(*i)++;
	while (str[*i] != '\'' && str[*i])
		(*i)++;
}

void	search_dq(char *str, int *i)
{
	(*i)++;
	while (str[*i] != '\"' && str[*i])
		(*i)++;
}

int	ds_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			search_sq(str, &i);
			if (str[i] != '\'')
			{
				printf("bash: syntax error\n");
				return (1);
			}
		}
		else if (str[i] == '\"')
		{
			search_dq(str, &i);
			if (str[i] != '\"')
			{
				printf("bash: syntax error\n");
				return (1);
			}
		}
	}
	return (0);
}

int	double_pipe(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (pipeee(str, &i, &j) == 1)
				return (1);
		}
		else if (str[i] == '>')
		{
			if (rederectionnn(str, &i, &j) == 1)
				return (1);
		}
		else if (str[i] == '<')
		{
			if (infileee(str, &i, &j) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
