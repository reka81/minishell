/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:25:37 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/06 16:08:39 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ambigious_redi(t_stack *a, t_stack *tmp, int *j)
{
	if (a->type == 6)
	{
		if (a->next)
		{
			if (tmp->type == 3 && a->next->value == NULL && ft_strcmp(tmp->value, "|") != 0)
			{
				*j = 1;
				dprintf(2, "bash: %s: ambiguous redirect\n",
					a->next->was);
			}
		}
	}
	else
	{
		if (tmp->type == 3 && a->value == NULL && ft_strcmp(tmp->value, "|") != 0)
		{
			*j = 1;
			dprintf(2, "bash: %s: ambiguous redirect\n", a->was);
		}
	}
}

void	print_ambigious(t_stack *a)
{
	t_stack		*tmp;
	static int	j = 0;

	while (a)
	{
		if (a->value)
		{
			if (ft_strcmp(a->value, "|") == 0)
				j = 0;
		}
		tmp = a;
		a = a->next;
		if (a && j == 0)
		{
			print_ambigious_redi(a, tmp, &j);
		}
		if (!a)
			j = 0;
	}
}

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

int	main(int ac, char **av, char **env)
{
	t_stack		*a;
	t_hxh		*final_linked;
	t_env		*environment;
	t_main		*main_fun;

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
	g_is_in_mini = 0;
	main_fun->current_path = NULL;
	main_fun->old_path = NULL;
	setup_signal_handlers(&main_fun->exit_status);
	routine(a, main_fun, &environment, final_linked);
}
