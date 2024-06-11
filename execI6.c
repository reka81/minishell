/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:04:55 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/11 15:23:28 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close1(t_hxh *final_linked)
{
	dup2(final_linked->input, 0);
	close(final_linked->input);
}

void	dup_close2(t_hxh *final_linked)
{
	dup2(final_linked->output, 1);
	close(final_linked->output);
}

void	dup_close3(int *fd)
{
	dup2(fd[1], 1);
	close(fd[1]);
}

void	expo2(t_hxh *final_linked,
	t_env *environment, t_exec *var, int *exit_status)
{
	export2(final_linked, environment, var, exit_status);
	exit(*exit_status);
}

void	execve1(char *path, char **arg, char **env)
{
	execve(path, arg, env);
	perror("execve1");
	exit(1);
}
