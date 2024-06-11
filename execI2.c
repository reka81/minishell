/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:24:10 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/10 17:49:34 by mettalbi         ###   ########.fr       */
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

t_env	*check_if_var2(t_env *environment, char *variable)
{
	char	*new;

	while (environment)
	{
		new = zyalloc(ft_strlen(environment->variable) + 2);
		new = new_var_woutequal(environment->variable);
		if (strcmp(new, variable) == 0)
		{
			return (environment);
		}
		environment = environment->next;
	}
	return (NULL);
}

t_env	*check_if_var(t_env *environment, char *variable)
{
	char	*new;
	char	*new2;

	new2 = new_var_woutequal(variable);
	while (environment)
	{
		new = zyalloc(ft_strlen(environment->variable) + 2);
		new = new_var_woutequal(environment->variable);
		if (strcmp(new, new2) == 0)
		{
			if (environment->variable
				[ft_strlen(environment->variable) - 1] != '=')
				environment->variable = ft_strjoin(environment->variable, "=");
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
