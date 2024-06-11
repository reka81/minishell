/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_fs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:19:07 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/10 22:01:42 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**store_env_2darr(t_env *environment)
{
	char	**strs;
	int		i;

	if (!environment)
		return (NULL);
	i = 0;
	strs = zyalloc((ft_lstsize1(environment) * 2) * sizeof(char *));
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

char	*ft_get_env1(char *val, t_env *enviroment)
{
	char	*new;

	while (enviroment != NULL)
	{
		new = new_val_woutequal(enviroment->value);
		if (ft_strcmp(val, new) == 0)
		{
			return (enviroment->variable);
		}
		enviroment = enviroment->next;
	}
	return (NULL);
}

char	*new_val_woutequal(char *value)
{
	char		*new;
	int			i;

	new = zyalloc(ft_strlen1(value) + 1);
	i = 0;
	while (value[i])
	{
		new[i] = value[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
