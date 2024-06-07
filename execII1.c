/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:39:10 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/07 17:24:03 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pwd(t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->variable, "PWD=") == 0)
		{
			return (0);
		}
		env = env->next;
	}
	return (1);
}

void	emptying_old_pwd(t_env *environment)
{
	while (environment != NULL)
	{
		if (ft_strcmp(environment->variable, "OLDPWD=") == 0)
			environment->value[0] = '\0';
		environment = environment->next;
	}
}

int	cd_cmd1(char *user, int *exit_status, t_env *environment)
{
	user = ft_get_env("HOME", environment);
	if (user)
		chdir(user);
	else
	{
		printf("bash: cd: HOME not set\n");
		*exit_status = 1;
		return (1);
	}
	return (0);
}

void	cd_cmd(t_hxh *final_linked, t_env *environment, int *exit_status)
{
	char	*user;
	char	cwd[1024];

	user = NULL;
	if (final_linked->value[1])
	{
		if (chdir(final_linked->value[1]) != 0)
		{
			perror("chdir ");
			*exit_status = 1;
			return ;
		}
		else if (!getcwd(cwd, 1024))
		{
			ft_putstr_fd2(ERROR_GETCWD, 2);
			*exit_status = 1;
			return ;
		}
	}
	else
		if (cd_cmd1(user, exit_status, environment) == 1)
			return ;
	if (check_pwd(environment) == 1)
		emptying_old_pwd(environment);
}

void	ft_echo(t_hxh *lst, int *exit_status)
{
	int		i;

	while (lst != NULL)
	{
		if (ft_strcmp("echo", lst->value[0]) == 0)
		{
			if (lst->value[1] == NULL)
				ft_putchar_fd('\n', lst->output);
			i = 1;
			ft_echo2(&i, lst);
			while (lst->value[i])
			{
				ft_putstr_fd1(lst->value[i], lst->output);
				if (lst->value[i + 1])
					ft_putchar_fd(' ', lst->output);
				i++;
			}
			if (ft_cheak_n(lst->value[1]) == 1)
				ft_putchar_fd('\n', lst->output);
		}
		lst = lst->next;
	}
	*exit_status = 0;
}
