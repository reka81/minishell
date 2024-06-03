/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:51:24 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/03 19:35:59 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_c(int a)
{
	(void)a;
	if (g_is_in_mini == 2)
	{
		close(0);
		return ;
	}
	if (!g_is_in_mini || g_is_in_mini == 3)
	{
		if (a == SIGINT)
		{
			rl_replace_line("", 0);
			write (1, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		g_is_in_mini = 3;
	}
}

void	setup_signal_handlers(int *exit_status)
{
	(void)exit_status;
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctl_c);
}
