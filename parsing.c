/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:45:18 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/31 16:02:04 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fun(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			i++;
			while (str[i] != '\0')
			{
				if (str[i] != ' ')
					return (0);
				i++;
			}
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_parc1(char *str, int len)
{
	if (str[0] == '|')
	{
		printf("bash: syntax error\n");
		return (1);
	}
	else if (str[len] == '>' || str[len] == '<'
		|| str[len] == '|' || check_fun(str) == 1)
	{
		printf("bash: syntax error\n");
		return (1);
	}
	return (0);
}

int	ft_pars(char *str)
{
	int	len;
	int	i;

	len = strlen(str) - 1;
	if (len < 0)
		len = 0;
	if (str[0] == ' ')
	{
		i = 0;
		while (str[i] == ' ')
		{
			if (str[i + 1] == '|')
			{
				printf("bash: syntax error\n");
				return (1);
			}
			i++;
		}
	}
	if (ft_parc1(str, len) == 1)
		return (1);
	return (0);
}

int	pipeee(char *str, int *i, int *j)
{
	if (*i - 1 >= 0)
	{
		if (str[*i - 1] == '|' || str[*i + 1] == '|')
		{
			printf("bash: syntax error\n");
			return (1);
		}
		*j = *i + 1;
		if (str[*j] == ' ')
		{
			while (str[*j] && str[*j] == ' ')
			{
				if (str[*j + 1] == '|')
				{
					printf("bash: syntax error\n");
					return (1);
				}
				(*j)++;
			}
		}
	}
	return (0);
}
