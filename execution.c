/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:54:28 by mettalbi          #+#    #+#             */
/*   Updated: 2024/04/22 18:57:08 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ff()
{
	  int fd;
    char path[256];
    
    for(fd = 0; fd < 2500; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            if (fcntl(fd, F_GETPATH, path) != -1) {
                dprintf(2, "File descriptor %d is referencing: %s\n", fd, path);
            } else {
                dprintf(2, "File descriptor %d is not associated with an open file.\n", fd);
            }
        }
    }
}

void	ft_putstr_fd2(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
    // write(fd, " ", 1);
}
t_env *check_if_var(t_env *environment, char *variable)
{
	while(environment)
	{
		if(!strcmp(environment->variable, variable))
			return(environment);
		environment = environment->next;
	}
	return(NULL);
}

int	check_if_value(char **str)
{
	int j = 0;
	int i = 0;
	
	while(str[i][j])	
	{	
		if(str[i][j] == '=')
			return(1);
		j++;
	}
	return(0);
}
void	afterwards_assignment(t_hxh *final_linked, t_env *environment, t_env *tmp)
{
	char *variable;
	char *value;
	int j;
	int i;
	
	j = 0;
	i = 0;
	variable = malloc(strlen(final_linked->value[0]) + 1);
	while(final_linked->value[0][i] && final_linked->value[0][i] != '=')
	{
		variable[i] = final_linked->value[0][i];
		i++;
	}
	variable[i] = '\0';
	if(i > 0)
		i++;
	j = 0;
	value = malloc(strlen(final_linked->value[0]) + 1);
	while(final_linked->value[0][i])
	{
		value[j] = final_linked->value[0][i];
		j++;
		i++;
	}
	value[j] = '\0';
	tmp = check_if_var(environment, variable);
	if(tmp)
	{
		free(tmp->value);
		tmp->value = value;
	}
	else
		free(value);
	free(variable);
}
void no_args_export(t_env *environment, t_hxh *final_linked)
{
	while(environment)
	{
		if(environment->variable)
		{
			ft_putstr_fd2("declare -x ", final_linked->output);
			ft_putstr_fd2(environment->variable, final_linked->output);
		}
		if(environment->value)
		{
			ft_putstr_fd2("= \"", final_linked->output);
			ft_putstr_fd2(environment->value , final_linked->output);
			ft_putstr_fd2("\"\n", final_linked->output);
		}
		environment = environment->next;
	}
}	
void setting_var_and_val(char **variable, char **value, t_hxh *final_linked, int d)
{
	int i;
	int j;
	
	i = 0;
	*variable = malloc(strlen(final_linked->value[d]) + 1);
	while(final_linked->value[d][i] && final_linked->value[d][i] != '=')
	{
		variable[0][i] = final_linked->value[d][i];
		i++;
	}
	variable[0][i] = '\0';
	j = 0;
	if(i > 0 && final_linked->value[1][i])	
	{
		i++;
	}
	*value = malloc(strlen(final_linked->value[d]) + 1);
	while(final_linked->value[d][i])
	{
		value[0][j] = final_linked->value[d][i];
		j++;
		i++;
	}
	value[0][j] = '\0';
}
void normal_exporting(char *variable, char *value, t_hxh *final_linked, t_env *environment)
{
	t_env *tmp;
	
	if(variable[0] == '\0')
	{
		printf("bash: export: %s :not a valid identifier\n", value);
		if(final_linked->value[2])
			printf("bash: export: %s :not a valid identifier\n", final_linked->value[2]);
		free(value);
	}
	else
	{
		tmp = check_if_var(environment, variable);
		if(!tmp)
			ft_lstadd_back2(&environment, ft_lstnew2(variable, value));
		else
		{
			free(tmp->value);
			tmp->value = value;
		}
	}
}
void export(t_hxh *final_linked, t_env *environment, char *variable, char *value)
{
	t_env *tmp;
	int d;

	d = 1;
	if(check_if_value(final_linked->value))
		afterwards_assignment(final_linked, environment, tmp);
	else if(!final_linked->value[1])
		no_args_export(environment, final_linked);
	else
	{
		d = 1;
		while(final_linked->value[d])	
		{	
			setting_var_and_val(&variable, &value ,final_linked ,d);
			normal_exporting(variable, value, final_linked, environment);
			d++;
		}
	}
}
char **fill_args(t_hxh *final_linked)
{
	int i;
	char **arg = malloc(sizeof(char *) * 5);
	i = 0;
	while(final_linked->value[i])	
	{
		arg[i] = final_linked->value[i];
		i++; 
	}
	arg[i] = NULL;
	return(arg);
}

int execute_cmds(t_hxh *final_linked, int i,char **env, t_env *environment)
{
	int fd[2];
	char **arg = NULL;
	int ex = 0;
	
	pipe(fd);
	int pid = fork();
	arg = fill_args(final_linked);
	char *path = look_for_path(final_linked->value[0], ft_get_env("PATH", environment));
	if(pid == 0)
	{
		close(fd[0]);
		if(final_linked->input != 0)
		{
			dup2(final_linked->input, 0);
			close(final_linked->input);
		}
		if(final_linked->output != 1)
		{
			dup2(final_linked->output, 1);
			close(final_linked->output);
		}
		else
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		execve(path, arg, env);
		perror("execve1");
		exit(1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		// waitpid(pid, &ex, 0);
	}
	ex++;
	return (pid);
}

void execution(t_env *environment, t_hxh *final_linked, char **env, int exit_status)
{
	char *value;
	char *variable;
	char cwd[1024];
	char *user;
	int pid;
	char *path;
	int *pid_tab;
	int i;
	int num_of_elems;
	
	i = 0;
	if (final_linked->next == NULL)
	{
		if(!strcmp(final_linked->value[0], "pwd"))
		{
			getcwd(cwd, sizeof(cwd));
			ft_putstr_fd(cwd, final_linked->output);
		}
		else if(!strcmp(final_linked->value[0], "export") || check_if_value(final_linked->value))
			export(final_linked, environment, variable, value);
		else if(!strcmp(final_linked->value[0], "env"))
		{
			while(environment)
			{
				if(environment->value[0] != '\0' && environment->variable[0] != '\0')
					printf("%s=%s\n", environment->variable, environment->value);
				environment = environment->next;
			}
		}
		else if(!strcmp(final_linked->value[0], "cd"))
		{
			if(final_linked->value[1])
			{
				chdir(final_linked->value[1]);
				
			}
			else
			{	
				user = ft_get_env("HOME", environment);
				if(user)
					chdir(user);
				else
					printf("bash: cd: HOME not set\n");
			}
		}
		else if(!strcmp(final_linked->value[0], "echo"))
			ft_echo(final_linked);
		else if(!strcmp(final_linked->value[0], "unset"))
			ft_unset(final_linked, &environment);
		else if(!strcmp(final_linked->value[0], "exit"))
			ft_exit(final_linked);
		else
		{
			dup2(final_linked->input, 0);
			dup2(final_linked->output , 1);
			pid = fork();
			if(pid == 0)
			{
				path =look_for_path(final_linked->value[0], ft_get_env("PATH", environment));
				execve(path , final_linked->value, env);
			}
			waitpid(pid, &exit_status, 0);
		}
	}
	else
	{
		
		int a = ft_lstsize(final_linked);
		num_of_elems = a;
		pid_tab = malloc(a * 4);
		dup2(final_linked->input, 0);
		while(a > 1)
		{	
			pid_tab[i] = execute_cmds(final_linked, exit_status, env, environment);
			final_linked = final_linked->next;
			a--;
			i++;
		}
		pid = fork();
		pid_tab[i] = pid;
		char **arg = fill_args(final_linked);
		if (pid == 0)
		{
			char *path2 = look_for_path(final_linked->value[0], ft_get_env("PATH", environment));
			execve(path2, arg, env);	
			perror("execve2");
			exit(1);
		}
		else
		{
			i = 0;
			while(i < num_of_elems)
			{
				// printf("%d\n", pid_tab[i]);
				waitpid(pid_tab[i], &exit_status, 0);
				i++;
			}
			// while((wait(NULL) != -1));
		}
		// while(i < 2)
		// {
		// 	printf("%d\n", pid_tab[i]);
		// 	i++;
		// }
	}
}
