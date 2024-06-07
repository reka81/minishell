/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:10:39 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/07 18:47:06 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_v1(t_env **env, t_hxh *lst, int i, t_env *tmp3)
{
	t_env	*tmp1;
	t_env	*tmp;
	char	*str;
	char	*str1;

	while (*env != NULL)
	{
		str1 = ft_rm_equal(tmp3->variable);
		str = ft_rm_equal((*env)->variable);
		if (ft_strcmp(lst->value[i], str1) == 0)
		{
			tmp3 = tmp3->next;
			*env = tmp3;
		}
		else if (ft_strcmp(lst->value[i], str) == 0)
		{
			tmp1 = (*env)->next;
			*env = tmp;
			(*env)->next = tmp1;
		}
		tmp = (*env);
		if (*env)
			(*env) = (*env)->next;
	}
	*env = tmp3;
}

void	ft_unset(t_hxh *lst, t_env **env, int *exit_status)
{
	int		i;
	t_env	*tmp3;

	if (ft_strcmp(lst->value[0], "unset") == 0)
	{
		if (not_valid(lst->value) == 1)
		{
			*exit_status = 1;
			return ;
		}
		else
			*exit_status = 0;
		i = 1;
		while (lst->value[i])
		{
			tmp3 = *env;
			ft_unset_v1(env, lst, i, tmp3);
			i++;
		}
	}
}

void	close_fd(t_hxh *final_linked)
{
	if (final_linked->output != 1)
		close(final_linked->output);
}

void	one_command(t_hxh *final_linked, t_env **environment,
		t_exec1 *var, int *exit_status)
{
	if (final_linked->shouldnt_run != 5)
	{
		if (!strcmp(final_linked->value[0], "pwd"))
			pwd_cmd(final_linked);
		else if (!strcmp(final_linked->value[0], "export")
			|| check_if_value(final_linked->value))
			export(final_linked, *environment, var, exit_status);
		else if (!strcmp(final_linked->value[0], "env"))
			env_cmd2(*environment, final_linked->output);
		else if (!strcmp(final_linked->value[0], "cd"))
			cd_cmd(final_linked, *environment, exit_status);
		else if (!strcmp(final_linked->value[0], "echo"))
			ft_echo(final_linked, exit_status);
		else if (!strcmp(final_linked->value[0], "unset"))
			ft_unset(final_linked, environment, exit_status);
		else if (!strcmp(final_linked->value[0], "exit"))
			(ft_exit(final_linked, exit_status));
		else
			not_builtins(final_linked, var, *environment, exit_status);
	}
	else
		*exit_status = 1;
	if (final_linked->input != 0)
		close(final_linked->input);
	close_fd(final_linked);
}

void	execution(t_env **environment, t_hxh *final_linked,
		char **env, int *exit_status)
{
	t_exec1	*var;

	var = zyalloc(sizeof(t_exec1));
	var->i = 0;
	var->path = NULL;
	var->env = env;
	var->exit_status = exit_status;
	if (final_linked->next == NULL)
	{
		if (final_linked->value[0] == NULL)
			return ;
		one_command(final_linked, environment, var, exit_status);
	}
	else
	{
		primary_pipes(var, final_linked, env, *environment);
	}
}
