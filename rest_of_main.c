/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_of_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:30:37 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/03 22:10:06 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flaging_expandables(t_stack *a)
{
	while (a)
	{
		if (strcmp(a->value, "<<") == 0)
		{
			if (a->next->type == 6)
				a->next->next->should_be_exp = 1;
			else
				a->next->should_be_exp = 0;
		}
		a = a->next;
	}
}

int	cmp_delim(char c)
{
	int		i;
	char	*delim;

	i = 0;
	delim = "~!@#$%^&*-+=.?,";
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	filling_env2(t_filling_env *fill, char **env)
{
	fill->e = 0;
	fill->j = 0;
	fill->variable = zyalloc(strlen(env[fill->i]) + 1);
	while (env[fill->i][fill->e] && env[fill->i][fill->e] != '=')
	{
		fill->variable[fill->j] = env[fill->i][fill->e];
		fill->j++;
		fill->e++;
	}
	fill->variable[fill->j] = '=';
	fill->j++;
	fill->variable[fill->j] = '\0';
}

void	filling_env(char **env, t_env **environment)
{
	t_filling_env	*fill;

	fill = zyalloc(sizeof(t_filling_env));
	fill->i = 0;
	while (env[fill->i])
	{
		filling_env2(fill, env);
		fill->j = 0;
		fill->value = zyalloc(strlen(env[fill->i]) + 1);
		fill->e++;
		while (env[fill->i][fill->e])
		{
			fill->value[fill->j] = env[fill->i][fill->e];
			fill->j++;
			fill->e++;
		}
		fill->value[fill->j] = '\0';
		ft_lstadd_back2(environment, ft_lstnew2(fill->variable, fill->value));
		fill->i++;
	}
}

char	*ft_update_pwd(t_env *environment, char *current_path, char *old_path)
{
	while (environment != NULL)
	{
		if (strcmp("PWD=", environment->variable) == 0)
		{
			current_path = getcwd(0, 0);
			environment->value = current_path;
		}
		if (current_path && old_path)
		{
			if (strcmp("OLDPWD=", environment->variable) == 0 && old_path != NULL
				&& ft_strcmp(old_path, current_path) != 0)
			{
				environment->value = old_path;
			}
		}
		environment = environment->next;
	}
	return (current_path);
}
