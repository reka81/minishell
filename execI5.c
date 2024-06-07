/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:00:24 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/07 18:21:16 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_decision(char *variable, char *new,
	t_env *tmp, t_env *environment)
{
	new = new_var_woutpls(variable);
	tmp = check_if_var(environment, new);
}

int	normal_exporting(char *variable, char *value,
	t_hxh *final_linked, t_env *environment)
{
	t_env	*tmp;
	char	*new;

	(1) && (new = NULL, tmp = NULL);
	if ((value[0] == '\0' && check_if_pls2(variable))
		|| ft_isdigit(variable[0]) || check_if_dlm(variable))
	{
		(ft_putstr_fd2("bash: export: `", 2), ft_putstr_fd2(variable, 2),
			ft_putstr_fd2("': not a valid identifier\n", 2));
		return (1);
	}
	else if (variable[0] == '\0')
	{
		exp_n_valid(final_linked, value);
		return (1);
	}
	else
	{
		export_decision(variable, new, tmp, environment);
		if (!tmp)
			ft_lstadd_back2(&environment, ft_lstnew2(new, value));
		else
			join_or_not(value, variable, tmp);
	}
	return (0);
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

void	updating_exite_status(int check, int *exit_status)
{
	if (check == 1)
		*exit_status = 1;
	else
		*exit_status = 0;
}

void	export(t_hxh *final_linked, t_env *environment,
			t_exec1 *var, int *exit_status)
{
	t_env	*tmp;
	int		d;
	int		check;

	d = 1;
	tmp = NULL;
	check = 0;
	if (check_if_value(final_linked->value))
		afterwards_assignment(final_linked, environment, tmp);
	else if (!final_linked->value[1])
		no_args_export(final_linked, var->env);
	else
	{
		d = 1;
		while (final_linked->value[d])
		{
			setting_var_and_val(&var->variable, &var->value,
				final_linked, d);
			check = normal_exporting(var->variable, var->value,
					final_linked, environment);
			d++;
		}
	}
	updating_exite_status(check, exit_status);
}
