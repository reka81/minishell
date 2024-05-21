/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_fs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:19:07 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/21 15:22:21 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**store_env_2darr(t_env *environment)
{
	char	**strs;
	int		i;

	i = 0;
	strs = zyalloc(1000);
	while (environment != NULL)
	{
		strs[i] = ft_strjoin(environment->variable, environment->value);
		i++;
		environment = environment->next;
	}
	strs[i] = NULL;
	return (strs);
}

char	*ft_get_env(char *var, t_env *enviroment)
{
	char	*new;

	while (enviroment != NULL)
	{
		new = new_var_woutequal(enviroment->variable);
		if (ft_strcmp(var, new) == 0)
		{
			return (enviroment->value);
		}
		enviroment = enviroment->next;
	}
	return (NULL);
}
