/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:52:47 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/11 15:17:14 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_decision(char *variable, char *new,
	t_env **tmp, t_env *environment)
{
	new = new_var_woutpls(variable);
	*tmp = check_if_var(environment, new);
	return (new);
}

void	join_or_not(char *value, char *variable, t_env *tmp)
{
	if (check_if_pls2(variable))
	{
		tmp->value = ft_strjoin(tmp->value, value);
	}
	else
	{
		tmp->value = value;
	}
}

void	ft_echo3(t_hxh *lst, int *exit_status)
{
	int		i;

	while (lst != NULL)
	{
		if (ft_strcmp("echo", lst->value[0]) == 0)
		{
			if (lst->value[1] == NULL)
				printf("\n");
			i = 1;
			ft_echo2(&i, lst);
			while (lst->value[i])
			{
				printf("%s\n", lst->value[i]);
				if (lst->value[i + 1])
					ft_putchar_fd(' ', lst->output);
				i++;
			}
			if (ft_cheak_n(lst->value[1]) == 1)
				printf("\n");
		}
		lst = lst->next;
	}
	*exit_status = 0;
}

void	checking_them2(t_exec *var, t_hxh *final_linked, t_env *environment)
{
	if (!ft_strcmp(var->arg[0], "export"))
		expo2(final_linked, environment, var, var->exit_status);
	else if (!ft_strcmp(var->arg[0], "exit"))
		(ft_exit2(final_linked, var->exit_status), exit(*var->exit_status));
	else if (!ft_strcmp(var->arg[0], "pwd"))
		(pwd_cmd2(final_linked), exit(0));
	else if (!ft_strcmp(final_linked->value[0], "unset"))
		(ft_unset(final_linked, &environment, var->exit_status),
			exit(*var->exit_status));
	else if (!ft_strcmp(final_linked->value[0], "echo"))
		(ft_echo(final_linked, var->exit_status), exit(*var->exit_status));
	else if (!ft_strcmp(final_linked->value[0], "env"))
		(env_cmd(environment), exit(0));
	else if (!ft_strcmp(final_linked->value[0], "cd"))
		(cd_cmd(final_linked, environment, var->exit_status),
			exit(*var->exit_status));
}

void	checking_them(t_hxh *final_linked, t_env *environment, t_exec1 *var)
{
	if (!ft_strcmp(final_linked->value[0], "export"))
		(export(final_linked, environment, var, var->exit_status),
			exit(*var->exit_status));
	else if (!ft_strcmp(final_linked->value[0], "exit"))
		(ft_exit2(final_linked, var->exit_status), exit(*var->exit_status));
	else if (!ft_strcmp(final_linked->value[0], "pwd"))
		(pwd_cmd2(final_linked), exit(0));
	else if (!ft_strcmp(final_linked->value[0], "unset"))
		(ft_unset(final_linked, &environment, var->exit_status),
			exit(*var->exit_status));
	else if (!ft_strcmp(final_linked->value[0], "echo"))
		(ft_echo(final_linked, var->exit_status), exit(*var->exit_status));
	else if (!ft_strcmp(final_linked->value[0], "env"))
		(env_cmd(environment), exit(0));
	else if (!ft_strcmp(final_linked->value[0], "cd"))
		(cd_cmd(final_linked, environment, var->exit_status),
			exit(*var->exit_status));
}
