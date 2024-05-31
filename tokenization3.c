/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:37:19 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/31 13:36:48 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_is_in_mini;

void	clean_final(t_hxh *final_linked)
{
	int	i;

	i = 0;
	while (final_linked)
	{
		clean_final2(final_linked, i);
		if (final_linked)
			final_linked = (final_linked)->next;
		i++;
	}
}

int	check_if_faulty(t_hxh *a)
{
	while (a)
	{
		if (a->is_faulty == 2 || a->ambigious == 20
			|| !a->value[0] || a->ambigious == 30)
		{
			if (a->shouldnt_run != 5)
				return (1);
		}
		a = a->next;
	}
	return (0);
}

void	rest_of_main2(t_stack *a, t_hxh *final_linked,
	t_env **environment, t_main *main_fun)
{
	int	fd;

	if (a)
	{
		if (a->type == 6 && a->next == NULL)
			freeing_pr(&a);
	}
	if (a)
	{
		fd = dup(0);
		final_linked = ft_store(a, *environment);
		(dup2(fd, 0), close(fd));
		while (check_if_faulty(final_linked))
			clean_final(final_linked);
		if (final_linked)
		{
			g_is_in_mini = 1;
			execution(environment, final_linked,
				main_fun->envi2, &main_fun->exit_status);
			g_is_in_mini = 0;
			main_fun->old_path = main_fun->buf;
			main_fun->buf = ft_update_pwd(*environment,
					main_fun->current_path, main_fun->old_path);
		}
	}
}

void	rest_of_main(t_main *main_fun, t_stack *a
		, t_env **environment, t_hxh *final_linked)
{
	if (main_fun->l[0] == '\0')
	{
		free(main_fun->l);
		main_fun->l = NULL;
	}
	if (main_fun->l)
	{
		if (!double_pipe(main_fun->l)
			&& !ds_quotes(main_fun->l) && !ft_pars(main_fun->l))
		{
			tokenization(&a, main_fun->l);
			flaging_expandables(a);
			expanding(a, main_fun->exit_status, *environment);
			print_ambigious(a);
			while (check_if_null(a))
				ft_rm_null(&a);
			rest_of_main2(a, final_linked, environment, main_fun);
		}
		free(main_fun->l);
	}
}

t_env	*ft_lstnew5(char *variable, char *value)
{
	t_env	*s1;

	s1 = zyalloc(sizeof(t_env));
	if (!s1)
		return (NULL);
	s1->variable = variable;
	s1->value = value;
	s1->next = NULL;
	return (s1);
}
