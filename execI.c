/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:54:28 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/30 21:11:52 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		dup2(final_linked->output, 1);
		close(final_linked->output);
	}
	if (is_apath(final_linked->value[0]))
		var->path2 = ft_strmcpy(var->path, final_linked->value[0]);
	else
		var->path2 = look_for_path(final_linked->value[0],
				ft_get_env("PATH", environment));
	if (final_linked->shouldnt_run != 5)
	{
		if (execve(var->path2, arg, env) == -1)
			(dprintf(2, "bash : %s:command not found\n",
					final_linked->value[0]), exit(127));
	}
	exit (1);
}

void	waiting_for_children(int fd_out, int fd_in, t_exec1 *var)
{
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	close(fd_out);
	close(fd_in);
	var->i = 0;
	while (var->i < var->num_of_elems)
	{
		waitpid(var->pid_tab[var->i], var->exit_status, 0);
		var->i++;
	}
	if (WIFSIGNALED(*var->exit_status))
	{
		if (WTERMSIG(*var->exit_status) == 2)
			printf("\n");
		if (WTERMSIG(*var->exit_status) == 3)
		{
			printf("Quit: 3\n");
			tcsetattr(STDIN_FILENO, TCSANOW, &var->my_termios);
		}
		*var->exit_status = 128 + WTERMSIG(*var->exit_status);
	}
	else
		*var->exit_status = WEXITSTATUS(*var->exit_status);
}

void	setting_values5(t_exec1 *var, t_hxh *final_linked)
{
	var->a = ft_lstsize(final_linked);
	var->num_of_elems = var->a;
	var->pid_tab = zyalloc(var->a * 4);
	dup2(final_linked->input, 0);
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
		var->pid_tab[var->i] = execute_cmds(final_linked, env, environment);
		close_fds(final_linked);
		final_linked = final_linked->next;
		var->a--;
		var->i++;
		if (var->a == 1 && final_linked->shouldnt_run != 5)
		{
			var->pid = fork();
			var->pid_tab[var->i] = var->pid;
			if (var->pid == 0)
				last_pipe(final_linked, env, environment, var);
			close_fds(final_linked);
		}
	}
	waiting_for_children(fd_out, fd_in, var);
}
