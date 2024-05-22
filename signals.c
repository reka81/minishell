/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:51:24 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/22 16:30:26 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_c(int a)
{
	extern int	g_is_in_mini;

	(void)a;
	if (!g_is_in_mini)
	{
		if (a == SIGINT)
		{
			rl_replace_line("", 0);
			write (1, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	setup_signal_handlers(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctl_c);
}
