/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:54:28 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/13 18:09:19 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	runing_cmd(t_hxh *final_linked, char **env,
	t_env *environment, t_exec1 *var)
{
	char	**arg;

	arg = fill_args(final_linked);
	checking_them(final_linked, environment, var);
	if (final_linked->shouldnt_run != 5)
	{
		if (execve(var->path2, arg, env) == -1)
		{
			ft_putstr_fd2("bash : ", 2);
			ft_putstr_fd2(final_linked->value[0], 2);
			ft_putstr_fd2(":command not found\n", 2);
			exit(127);
		}
	}
}

void	last_pipe(t_hxh *final_linked, char **env,
		t_env *environment, t_exec1 *var)
{
	char	**arg;

	arg = fill_args(final_linked);
	if (final_linked->input != 0)
	{
		dup2(final_linked->input, 0);
		close(final_linked->input);
	}
	if (final_linked->output != 1)
		(dup2(final_linked->output, 1), close(final_linked->output));
	if (is_apath(final_linked->value[0]))
	{
		var->path2 = ft_strmcpy(var->path, final_linked->value[0]);
		if (access(var->path2, F_OK) == -1)
			(ft_putstr_fd2("bash : ", 2), ft_putstr_fd2(var->path2, 2),
				ft_putstr_fd2(": No such file or directory\n", 2), exit(127));
		else if (access(var->path2, R_OK) == -1)
			(ft_putstr_fd2("bash: ", 2), ft_putstr_fd2(var->path2, 2),
				ft_putstr_fd2(": permision denied\n", 2), exit(126));
	}
	else
		var->path2 = look_for_path(final_linked->value[0],
				ft_get_env("PATH", environment));
	runing_cmd(final_linked, env, environment, var);
	exit (1);
}

void	setting_values5(t_exec1 *var, t_hxh *final_linked)
{
	var->a = ft_lstsize(final_linked);
	var->num_of_elems = var->a;
	var->pid_tab = zyalloc(var->a * 4);
	dup2(final_linked->input, 0);
}

void	is_last_pipe(t_exec1 *var, t_hxh *final_linked,
	char **env, t_env *environment)
{
	if (var->pid == 0)
	{
		if (final_linked->value[0] == NULL)
			exit(0);
		last_pipe(final_linked, env, environment, var);
	}
}

void	primary_pipes(t_exec1 *var, t_hxh *final_linked,
		char **env, t_env *environment)
{
	int	fd_out;
	int	fd_in;

	fd_out = dup(1);
	fd_in = dup(0);
	setting_values5(var, final_linked);
	while (var->a > 1)
	{
		signal(SIGQUIT, ctl_c);
		tcgetattr(STDIN_FILENO, &var->my_termios);
		var->pid_tab[var->i] = execute_cmds(final_linked, env,
				environment, var->exit_status);
		close_fds(final_linked);
		final_linked = final_linked->next;
		var->a--;
		var->i++;
		if (var->a == 1)
		{
			var->pid = fork();
			var->pid_tab[var->i] = var->pid;
			is_last_pipe(var, final_linked, env, environment);
			close_fds(final_linked);
		}
	}
	waiting_for_children(fd_out, fd_in, var);
}
