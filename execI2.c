/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:24:10 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/16 17:04:04 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_pls(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i][j] != '=' && str[i][j])
	{
		if (str[i][j] == '+')
			return (1);
		j++;
	}
	return (0);
}

void	ft_putstr_fd2(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

t_env	*check_if_var2(t_env *environment, char *variable)
{
	char	*new;

	new = malloc(100);
	while (environment)
	{
		new = new_var_woutequal(environment->variable);
		if (strcmp(new, variable) == 0)
		{
			free (new);
			return (environment);
		}
		free (new);
		environment = environment->next;
	}
	return (NULL);
}

t_env	*check_if_var(t_env *environment, char *variable)
{
	while (environment)
	{
		if (strcmp(environment->variable, variable) == 0)
		{
			return (environment);
		}
		environment = environment->next;
	}
	return (NULL);
}

int	check_if_value(char **str)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (str[i][j])
	{
		if (str[i][j] == '=')
			return (1);
		j++;
	}
	return (0);
}
