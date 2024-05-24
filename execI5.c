/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:00:24 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/23 21:37:02 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_exporting(char *variable, char *value,
	t_hxh *final_linked, t_env *environment)
{
	t_env	*tmp;
	char	*new;

	new = NULL;
	if ((value[0] == '\0' && check_if_pls2(variable))
		|| ft_isdigit(variable[0]) || check_if_dlm(variable))
		printf("bash: export: `%s': not a valid identifier\n", variable);
	else if (variable[0] == '\0')
	{
		exp_n_valid(final_linked, value);
	}
	else
	{
		new = new_var_woutpls(variable);
		tmp = check_if_var(environment, new);
		if (!tmp)
			ft_lstadd_back2(&environment, ft_lstnew2(new, value));
		else
		{
			join_or_not(value, variable, tmp);
		}
	}
}

void	no_args_export2(t_env *environment)
{
	while (environment)
	{
		if (environment->variable)
		{
			printf("declare -x ");
			printf("%s", environment->variable);
		}
		if (environment->value)
		{
			printf("= \"");
			printf("%s", environment->value);
			printf("\"\n");
		}
		environment = environment->next;
	}
}

void	export2(t_hxh *final_linked, t_env *environment,
	char *variable, char *value)
{
	t_env	*tmp;
	int		d;

	d = 1;
	tmp = NULL;
	if (check_if_value(final_linked->value))
	{
		afterwards_assignment(final_linked, environment, tmp);
	}
	else if (!final_linked->value[1])
		no_args_export2(environment);
	else
	{
		d = 1;
		while (final_linked->value[d])
		{
			setting_var_and_val(&variable, &value, final_linked, d);
			normal_exporting(variable, value, final_linked, environment);
			d++;
		}
	}
}

void	export(t_hxh *final_linked, t_env *environment,
	char *variable, char *value)
{
	t_env	*tmp;
	int		d;

	d = 1;
	tmp = NULL;
	if (check_if_value(final_linked->value))
	{
		afterwards_assignment(final_linked, environment, tmp);
	}
	else if (!final_linked->value[1])
		no_args_export(environment, final_linked);
	else
	{
		d = 1;
		while (final_linked->value[d])
		{
			setting_var_and_val(&variable, &value, final_linked, d);
			normal_exporting(variable, value, final_linked, environment);
			d++;
		}
	}
}

char	**fill_args(t_hxh *final_linked)
{
	int		i;
	char	**arg;

	arg = zyalloc(sizeof(char *) * 5);
	i = 0;
	while (final_linked->value[i])
	{
		arg[i] = final_linked->value[i];
		i++;
	}
	arg[i] = NULL;
	return (arg);
}
