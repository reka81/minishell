/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:39:10 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/03 20:09:51 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_hxh *final_linked, t_env *environment)
{
	char	*user;
	char	cwd[1024];

	if (final_linked->value[1])
	{
		if (chdir(final_linked->value[1]) != 0)
			perror("chdir ");
		else if (!getcwd(cwd, 1024))
		{
			dprintf(2, ERROR_GETCWD);
		}
	}
	else
	{
		user = ft_get_env("HOME", environment);
		if (user)
		{
			chdir(user);
		}
		else
			printf("bash: cd: HOME not set\n");
	}
}

int	ft_cheak_n(char *str)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) == 1)
		return (1);
	while (str[i])
	{
		if ((str[0] != '-' || str[i] != 'n'))
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

void	ft_echo2(int *i, t_hxh *lst)
{
	while (lst->value[(*i)])
	{
		if (ft_cheak_n(lst->value[(*i)]) == 2)
			(*i)++;
		else
			break ;
	}
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
