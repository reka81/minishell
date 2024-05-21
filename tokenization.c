/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:25:37 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/21 14:31:57 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_null(t_stack *a)
{
	while (a)
	{
		if (a->value == NULL)
			return (1);
		a = a->next;
	}
	return (0);
}

void	freeing_pr(t_stack **a)
{
	*a = NULL;
}

void	fill_env3(char *variable, char *value, t_env **environment, int i)
{
	if (i == 1)
	{
		variable = fill(variable, "SHLVL=");
		value = fill(value, "1");
		ft_lstadd_back7(environment, ft_lstnew5(variable, value));
	}
	if (i == 2)
	{
		variable = fill(variable, "_=");
		value = fill(value, "/usr/bin/env");
		ft_lstadd_back7(environment, ft_lstnew5(variable, value));
	}
	if (i == 3)
	{
		variable = fill(variable, "PATH=");
		value = fill(value, "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		ft_lstadd_back7(environment, ft_lstnew5(variable, value));
	}
}

void	fill_env2(t_env **environment)
{
	int		i;
	char	*value;
	char	*variable;

	i = 0;
	value = zyalloc(50);
	*environment = NULL;
	while (i < 4)
	{
		if (i == 0)
		{
			variable = fill(variable, "PWD=");
			getcwd(value, 50);
			ft_lstadd_back7(environment, ft_lstnew5(variable, value));
		}
		fill_env3(variable, value, environment, i);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_stack	*a;
	t_hxh	*final_linked;
	t_env	*environment;
	t_main	*main_fun;

	a = NULL;
	final_linked = NULL;
	(void) ac;
	(void) av;
	environment = NULL;
	main_fun = zyalloc(sizeof(t_main));
	filling_env(env, &environment);
	if (!environment)
		fill_env2(&environment);
	main_fun->l = NULL;
	main_fun->exit_status = 0;
	main_fun->envi2 = store_env_2darr(environment);
	setup_signal_handlers();
	routine(a, main_fun, &environment, final_linked);
}
