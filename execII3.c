/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execII3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:46:12 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/11 17:13:52 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_dlm(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] == '\0')
		{
			if (cmp_w_dlm2(str[i]))
				return (1);
			return (0);
		}
		if (cmp_w_dlm(str[i], str[i + 1]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_exit(t_hxh *lst)
{
	ft_putstr_fd2("exit\n", 2);
	ft_putstr_fd2("bash: exit: ", 2);
	ft_putstr_fd2(lst->value[1], 2);
	ft_putstr_fd2(": numeric argument required", 2);
	exit(255);
}

void	ft_exit(t_hxh *lst, int *exit_status)
{
	if (!ft_strcmp(lst->value[0], "exit"))
	{
		if (lst->value[1])
		{
			if (ft_strdigit(lst->value[1]) == 1)
			{
				if (lst->value[2] != NULL)
				{
					ft_putstr_fd2("bash: exit: too many arguments\n", 2);
					*exit_status = 1;
					return ;
				}
				(exit(ft_atoi(lst->value[1])), ft_putstr_fd2("exit\n", 2));
			}
			else
				print_exit(lst);
		}
		else
		{
			ft_putstr_fd2("exit\n", 2);
			exit(0);
		}
	}
}

void	ft_exit2(t_hxh *lst, int *exit_status)
{
	if (!ft_strcmp(lst->value[0], "exit"))
	{
		if (lst->value[1])
		{
			if (ft_strdigit(lst->value[1]) == 1)
			{
				if (lst->value[2] != NULL)
				{
					ft_putstr_fd2("bash: exit: too many arguments\n", 2);
					*exit_status = 1;
					return ;
				}
				exit(ft_atoi(lst->value[1]));
			}
			else
			{
				ft_putstr_fd2("bash: exit: ", 2);
				ft_putstr_fd2(lst->value[1], 2);
				ft_putstr_fd2(": numeric argument required", 2);
				exit(255);
			}
		}
		else
			exit(0);
	}
}

void	exp_n_valid(t_hxh *final_linked, char *value)
{
	(ft_putstr_fd2("bash: export: `", 2), ft_putstr_fd2(value, 2),
		ft_putstr_fd2("': not a valid identifier\n", 2));
	if (final_linked->value[2])
		(ft_putstr_fd2("bash: export: `", 2),
			ft_putstr_fd2(final_linked->value[2], 2),
			ft_putstr_fd2("': not a valid identifier\n", 2));
}
