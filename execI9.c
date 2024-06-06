/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execI9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:14:09 by zaheddac          #+#    #+#             */
/*   Updated: 2024/06/06 21:22:09 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		*var->exit_status = WEXITSTATUS(*var->exit_status);
	}
}

char	**fill_args(t_hxh *final_linked)
{
	int		i;
	char	**arg;

	arg = zyalloc(sizeof(char *) * 5);
	i = 0;
	while (final_linked->value[i])
	{
		arg[i] = final_linked->value[i];
		i++;
	}
	arg[i] = NULL;
	return (arg);
}

void	env_cmd(t_env *environment)
{
	while (environment)
	{
		if ((environment->value[0] != '\0' && environment->variable[0] != '\0')
			|| check_if_equal(environment->variable))
			printf("%s%s\n", environment->variable, environment->value);
		environment = environment->next;
	}
}

void	pwd_cmd2(t_hxh *final_linked)
{
	char	cwd[1024];

	(void)final_linked;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
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
