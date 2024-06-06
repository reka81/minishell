/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:18:28 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/05 23:57:22 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close5(int fd_out, int fd_in)
{
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	checking_if_signal(int fd_out, int fd_in,
	int *exit_status, t_exec1 *var)
{
	waitpid(var->pid, exit_status, 0);
	if (WIFSIGNALED(*exit_status))
	{
		if (WTERMSIG(*exit_status) == 2)
			printf("\n");
		if (WTERMSIG(*exit_status) == 3)
		{
			printf("Quit: 3\n");
			tcsetattr(STDIN_FILENO, TCSANOW, &var->my_termios);
		}
		*exit_status = 128 + WTERMSIG(*exit_status);
	}
	else
		*exit_status = WEXITSTATUS(*exit_status);
	dup_close5(fd_out, fd_in);
}

void	not_builtins_v2(t_hxh *final_linked, t_exec1 *var,
	t_env *environment, int *exit_status)
{
	struct stat	st;

	signal(SIGQUIT, ctl_c);
	if (is_apath(final_linked->value[0]))
	{
		var->path = ft_strmcpy(var->path, final_linked->value[0]);
		if (access(var->path, F_OK) == -1)
			(dprintf(2, "bash: %s: No such file or directory\n", var->path), exit(127));
		else if (access(var->path, R_OK) == -1)
			(dprintf(2, "bash: %s: permision denied\n", var->path), exit(126));
	}
	else
		var->path = look_for_path(final_linked->value[0],
				ft_get_env("PATH", environment));
	if (final_linked->shouldnt_run != 5)
	{
		if (stat(var->path, &st) == 0 && S_ISDIR(st.st_mode))
			(dprintf(2, "bash: %s: is a directory\n", var->path), exit(126));
		if (execve(var->path, final_linked->value, var->env) == -1)
		{
			dprintf(2, "bash : %s:command not found\n",
				final_linked->value[0]);
			*exit_status = 127;
		}
		exit(127);
	}
	exit(1);
}

void	not_builtins(t_hxh *final_linked, t_exec1 *var,
	t_env *environment, int *exit_status)
{
	int	fd_out;
	int	fd_in;

	fd_out = dup(1);
	fd_in = dup(0);
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
	tcgetattr(STDIN_FILENO, &var->my_termios);
	var->pid = fork();
	if (var->pid == 0)
		not_builtins_v2(final_linked, var, environment, exit_status);
	else
		checking_if_signal(fd_out, fd_in, exit_status, var);
}

void	join_or_not(char *value, char *variable, t_env *tmp)
{
	if (check_if_pls2(variable))
	{
		tmp->value = ft_strjoin(tmp->value, value);
	}
	else
	{
		tmp->value = value;
	}
}
