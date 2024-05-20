/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:18:28 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/20 16:05:10 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close5(int fd_out, int fd_in)
{
	if (!isatty(STDOUT_FILENO))
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (!isatty(STDIN_FILENO))
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

void	not_builtins(t_hxh *final_linked, t_exec1 *var,
	t_env *environment, int *exit_status)
{
	int	fd_out;
	int	fd_in;

	fd_out = dup(1);
	fd_in = dup(0);
	dup2(final_linked->input, 0);
	dup2(final_linked->output, 1);
	tcgetattr(STDIN_FILENO, &var->my_termios);
	var->pid = fork();
	if (var->pid == 0)
	{
		signal(SIGQUIT, ctl_c);
		if (is_apath(final_linked->value[0]))
			var->path = ft_strmcpy(var->path, final_linked->value[0]);
		else
			var->path = look_for_path(final_linked->value[0],
					ft_get_env("PATH", environment));
		execve(var->path, final_linked->value, var->env);
		perror("execve");
		exit(1);
	}
	else
	{
		waitpid(var->pid, exit_status, 0);
		if(WIFSIGNALED(*exit_status))
		{
			if(WTERMSIG(*exit_status) == 2)
				printf("\n");
			if(WTERMSIG(*exit_status) == 3)
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
}

void	join_or_not(char *value, char *variable, char *new, t_env *tmp)
{
	if (check_if_pls2(variable))
	{
		tmp->value = ft_strjoin(tmp->value, value);
		// free(variable);
		// free(value);
		// free(new);
	}
	else
	{
		// free(tmp->value);
		tmp->value = value;
		// free(variable);
		// free(new);
	}
}

void	exp_n_valid(t_hxh *final_linked, char *value)
{
	printf("bash: export: %s :not a valid identifier\n", value);
	if (final_linked->value[2])
		printf("bash: export: %s :not a valid identifier\n",
			final_linked->value[2]);
	// free(value);
}
