/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:39:10 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/16 18:07:40 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_hxh *final_linked, t_env *environment)
{
	char	*user;

	if (final_linked->value[1])
		chdir(final_linked->value[1]);
	else
	{
		user = ft_get_env("HOME", environment);
		if (user)
			chdir(user);
		else
			printf("bash: cd: HOME not set\n");
	}
}

int	ft_cheak_n(char *str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!str)
		return (0);
	while (str[j])
	{
		if (str[0] != '-' || str[i] != 'n')
		{
			return (1);
		}
		i++;
		j++;
	}
	return (2);
}

int	ft_strdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_hxh *lst)
{
	int	i;

	while (lst != NULL)
	{
		if (ft_strcmp("echo", lst->value[0]) == 0)
		{
			if (lst->value[1] == NULL)
				ft_putchar_fd('\n', lst->output);
			i = ft_cheak_n(lst->value[1]);
			while (lst->value[i] && i > 0)
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
}

void	ft_exit(t_hxh *lst)
{
	if (!ft_strcmp(lst->value[0], "exit"))
	{
		if (lst->value[1])
		{
			if (ft_strdigit(lst->value[1]) == 1)
			{
				exit(atoi(lst->value[1]));
			}
			else
			{
				printf("bash: exit: %s: numeric argument required",
					lst->value[1]);
				exit(255);
			}
		}
		else
			exit(0);
	}
}
