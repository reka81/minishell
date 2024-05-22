/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:47:42 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/21 20:10:59 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_nvalid(char c)
{
	char	*str;
	int		i;

	str = "/*-+!@#$%^=";
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	not_valid(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (char_nvalid(strs[i][j]) == 1)
			{
				printf("bash: unset: `%s': not a valid identifier\n", strs[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_rm_equal(char *str)
{
	int		i;
	char	*nw_str;

	nw_str = zyalloc(strlen(str) + 1);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		nw_str[i] = str[i];
		i++;
	}
	nw_str[i] = '\0';
	return (nw_str);
}

void	free_env(t_env *env)
{
	free(env->variable);
	free(env->value);
	free(env);
}
