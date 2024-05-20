/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:54:28 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/20 15:46:59 by mettalbi         ###   ########.fr       */
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
	execve(var->path2, arg, env);
	perror("execve2");
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
	if(WIFSIGNALED(*var->exit_status))
	{
		if(WTERMSIG(*var->exit_status) == 2)
			printf("\n");
		if(WTERMSIG(*var->exit_status) == 3)
		{
			printf("Quit: 3\n");
			tcsetattr(STDIN_FILENO, TCSANOW, &var->my_termios);
		}
		*var->exit_status = 128 + WTERMSIG(*var->exit_status);	
	}
	else
		*var->exit_status = WEXITSTATUS(*var->exit_status);
}

void	primary_pipes(t_exec1 *var, t_hxh *final_linked,
	char **env, t_env *environment)
{
	int	fd_out;
	int	fd_in;

	fd_out = dup(1);
	fd_in = dup(0);
	var->a = ft_lstsize(final_linked);
	var->num_of_elems = var->a;
	var->pid_tab = malloc(var->a * 4);
	dup2(final_linked->input, 0);
	while (var->a > 1)
	{
		signal(SIGQUIT, ctl_c);
		tcgetattr(STDIN_FILENO, &var->my_termios);
		var->pid_tab[var->i] = execute_cmds(final_linked, env, environment);
		final_linked = final_linked->next;
		var->a--;
		var->i++;
		if (var->a == 1)
		{
			var->pid = fork();
			var->pid_tab[var->i] = var->pid;
			if (var->pid == 0)
				last_pipe(final_linked, env, environment, var);
		}
	}
	waiting_for_children(fd_out, fd_in, var);
}

void    one_command(t_hxh *final_linked, t_env **environment,
    t_exec1 *var, int *exit_status)
{
    if (!strcmp(final_linked->value[0], "pwd"))
        pwd_cmd(final_linked);
    else if (!strcmp(final_linked->value[0], "export")
        || check_if_value(final_linked->value))
        export(final_linked, *environment, var->variable, var->value);
    else if (!strcmp(final_linked->value[0], "env"))
        env_cmd(*environment);
    else if (!strcmp(final_linked->value[0], "cd"))
        cd_cmd(final_linked, *environment);
    else if (!strcmp(final_linked->value[0], "echo"))
        ft_echo(final_linked);
    else if (!strcmp(final_linked->value[0], "unset"))
        ft_unset(final_linked, environment, exit_status);
    else if (!strcmp(final_linked->value[0], "exit"))
        ft_exit(final_linked);
    else
        not_builtins(final_linked, var, *environment, exit_status);
}

void	execution(t_env **environment, t_hxh *final_linked,
	char **env, int *exit_status)
{
	t_exec1	*var;

	var = malloc(sizeof(t_exec1));
	var->i = 0;
	var->path = NULL;
	var->env = env;
	var->exit_status = exit_status;
	if (final_linked->value[0] == NULL)
		return ;
	if (final_linked->next == NULL)
		one_command(final_linked, environment, var, exit_status);
	else
		primary_pipes(var, final_linked, env, *environment);
}
