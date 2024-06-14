/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:27:05 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/14 18:11:58 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close4(int *fd)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	exec_cmd2(t_hxh *final_linked, t_exec *var, char **env)
{
	if (final_linked->shouldnt_run != 5 && final_linked->value[0])
	{
		if (execve(var->path, var->arg, env) == -1)
		{
			ft_putstr_fd2("bash : ", 2);
			ft_putstr_fd2(final_linked->value[0], 2);
			ft_putstr_fd2(":command not found\n", 2);
			exit(127);
		}
	}
}

void	ecexc_cmd1(t_exec *var, t_hxh *final_linked,
	t_env *environment, char **env)
{
	close(var->fd[0]);
	if (is_apath(final_linked->value[0]))
	{
		if (access(var->path, F_OK) == -1)
			(ft_putstr_fd2("bash : ", 2), ft_putstr_fd2(var->path, 2),
				ft_putstr_fd2(": No such file or directory\n", 2), exit(127));
		else if (access(var->path, R_OK) == -1)
			(ft_putstr_fd2("bash: ", 2), ft_putstr_fd2(var->path, 2),
				ft_putstr_fd2(": permision denied\n", 2), exit(126));
	}
	if (final_linked->input != 0)
		dup_close1(final_linked);
	if (final_linked->output != 1)
		dup_close2(final_linked);
	else
		dup_close3(var->fd);
	checking_them2(var, final_linked, environment);
	exec_cmd2(final_linked, var, env);
	if (!final_linked->value[0])
		exit(0);
	exit(1);
}

int	execute_cmds(t_hxh *final_linked, char **env,
	t_env *environment, int *exit_status)
{
	t_exec	*var;

	var = zyalloc(sizeof(t_exec));
	var->arg = NULL;
	var->ex = 0;
	pipe(var->fd);
	var->pid = fork();
	var->exit_status = exit_status;
	if (var->pid == 0)
	{
		if (final_linked->value[0] == NULL)
			exit(0);
		var->arg = fill_args(final_linked);
		if (is_apath(final_linked->value[0]))
			var->path = ft_strmcpy(var->path, final_linked->value[0]);
		else
			var->path = look_for_path(final_linked->value[0],
					ft_get_env("PATH", environment));
		ecexc_cmd1(var, final_linked, environment, env);
	}
	else
		dup_close4(var->fd);
	var->ex++;
	return (var->pid);
}

void	pwd_cmd(t_hxh *final_linked)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, final_linked->output);
}
