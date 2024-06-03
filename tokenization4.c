/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:48:12 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/03 19:41:55 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_hxh *final_linked)
{
	if (final_linked->input != 0)
		close(final_linked->input);
	if (final_linked->output != 1)
		close(final_linked->output);
}

void	clean_final2(t_hxh *final_linked, int i)
{
	if (final_linked->is_faulty == 2 || final_linked->ambigious == 20
		|| !final_linked->value[0] || final_linked->ambigious == 30)
	{
		if (i == 0)
		{
			close_fds(final_linked);
			final_linked->shouldnt_run = 5;
		}
		else if (final_linked->next != NULL)
		{
			close_fds(final_linked);
			final_linked->shouldnt_run = 5;
		}
		else if ((final_linked)->next == NULL)
		{
			close_fds(final_linked);
			(final_linked)->shouldnt_run = 5;
		}
	}
}

void	routine(t_stack *a, t_main *main_fun, t_env **environment,
		t_hxh *final_linked)
{
	main_fun->buf = 0;
	g_is_in_mini = 0;
	while (1)
	{
		main_fun->envi2 = store_env_2darr(*environment);
		a = NULL;
		main_fun->l = readline ("~$ :");
		if (g_is_in_mini == 3)
		{
			g_is_in_mini = 0;
			main_fun->exit_status = 1;
		}
		if (main_fun->l)
			main_fun->l = remove_tab(main_fun->l);
		if (!main_fun->l)
		{
			printf("exit\n");
			break ;
		}
		rest_of_main(main_fun, a, environment, final_linked);
	}
}

void	ft_lstadd_back7(t_env **lst, t_env *newnode)
{
	t_env	*start;

	if (!lst)
		return ;
	start = *lst;
	if (*lst)
	{
		while (start->next)
			start = start->next;
		start->next = newnode;
	}
	else
		*lst = newnode;
}

char	*fill(char *str1, char *str2)
{
	int	i;

	str1 = zyalloc(sizeof(char) * strlen(str2) + 1);
	i = 0;
	while (str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}
