/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:54:28 by mettalbi          #+#    #+#             */
/*   Updated: 2024/03/27 02:31:44 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void execution(t_env *environment, t_hxh *final_linked)
{
	char *value;
	char *variable;

	while(final_linked)
	{
		if(!strcmp(final_linked->value[0], "pwd"))
		{
			char *env = getenv("PWD");
			ft_putstr_fd(env, final_linked->output);
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
		return;
	}
}
