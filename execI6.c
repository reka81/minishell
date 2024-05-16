/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:04:55 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/16 17:45:15 by zaheddac         ###   ########.fr       */
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
	t_env *environment, char *variable, char *value)
{
	export2(final_linked, environment, variable, value);
	exit(0);
}

void	execve1(char *path, char **arg, char **env)
{
	execve(path, arg, env);
	perror("execve1");
	exit(1);
}
