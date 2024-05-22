/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:55:33 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/21 20:01:32 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	conflicted_redirictions1(char *str, int *j)
{
	if (str[*j + 1] == '>' || str[*j + 1] == '<')
	{
		printf("bash: syntax error\n");
		return (1);
	}
	return (0);
}

int	rederectionnn(char *str, int *i, int *j)
{
	if (str[*i + 1] == '<')
	{
		printf("bash: syntax error\n");
		return (1);
	}
	if (*i >= 2)
	{
		if ((str[*i - 1] == '>' && str[*i - 2] == '>')
			|| (str[*i + 1] == '>' && str[*i + 2] == '>'))
		{
			printf("bash: syntax error\n");
			return (1);
		}
	}
	*j = *i + 1;
	if (str[*j] == ' ')
	{
		while (str[*j] && str[*j] == ' ')
		{
			if (conflicted_redirictions1(str, j))
				return (1);
			(*j)++;
		}
	}
	return (0);
}

int	conflicted_redirictins(char *str, int *j)
{
	if (str[*j + 1] == '<' || str[*j + 1] == '>')
	{
		printf("bash: syntax error\n");
		return (1);
	}
	return (0);
}

int	infileee(char *str, int *i, int *j)
{
	if (str[*i + 1] == '>')
	{
		printf("bash: syntax error\n");
		return (1);
	}
	if (*i >= 2)
	{
		if ((str[*i - 1] == '<' && str[*i - 2] == '<')
			|| (str[*i + 1] == '<' && str[*i + 2] == '<'))
		{
			printf("bash: syntax error\n");
			return (1);
		}
	}
	*j = *i + 1;
	if (str[*j] == ' ')
	{
		while (str[*j] && str[*j] == ' ')
		{
			if (conflicted_redirictins(str, j))
				return (1);
			(*j)++;
		}
	}
	return (0);
}
