/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:38:27 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/31 13:38:46 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env3(char *variable, char *value, t_env **environment, int i)
{
	if (i == 1)
	{
		variable = fill(variable, "SHLVL=");
		value = fill(value, "1");
		ft_lstadd_back7(environment, ft_lstnew5(variable, value));
	}
	if (i == 2)
	{
		variable = fill(variable, "_=");
		value = fill(value, "/usr/bin/env");
		ft_lstadd_back7(environment, ft_lstnew5(variable, value));
	}
	if (i == 3)
	{
		variable = fill(variable, "PATH=");
		value = fill(value, "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		ft_lstadd_back7(environment, ft_lstnew5(variable, value));
	}
}

void	fill_env2(t_env **environment)
{
	int		i;
	char	*value;
	char	*variable;

	i = 0;
	value = zyalloc(50);
	*environment = NULL;
	while (i < 4)
	{
		if (i == 0)
		{
			variable = fill(variable, "PWD=");
			getcwd(value, 50);
			ft_lstadd_back7(environment, ft_lstnew5(variable, value));
		}
		fill_env3(variable, value, environment, i);
		i++;
	}
}
