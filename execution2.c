/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:47:42 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/11 21:47:43 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_cheak_n(char *str)
{
    int    i;
    int    j;

    i = 1;
    j = 0;
    if (!str)
        return (0);
    while (str[j])
    {
        if (str[0] != '-' || str[i] != 'n')
        {
            return (1);
        }
        i++;
        j++;
    }
    return (2);
}
int    ft_strdigit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            return (1);
        i++;
    }
    return (0);
}

void    ft_echo(t_hxh *lst)
{
    int    i;

    while (lst != NULL)
    {
        if (ft_strcmp("echo", lst->value[0]) == 0)
        {
            if(lst->value[1] == NULL)
                ft_putchar_fd('\n', lst->output);
            i = ft_cheak_n(lst->value[1]);
            while (lst->value[i] && i > 0)
            {
                ft_putstr_fd1(lst->value[i], lst->output);
                if (lst->value[i + 1])
                    ft_putchar_fd(' ', lst->output);
                i++;
            }
            if (ft_cheak_n(lst->value[1]) == 1)
                ft_putchar_fd('\n', lst->output);
        }
        lst = lst->next;
    }
}
void    ft_exit(t_hxh *lst)
{
    if (!ft_strcmp(lst->value[0], "exit"))
    {
        if (lst->value[1])
        {
            if (ft_strdigit(lst->value[1]) == 1)
            {
                exit(atoi(lst->value[1]));
            }
            else
            {
                printf("bash: exit: %s: numeric argument required", lst->value[1]);
                exit(255);
            }
        }
        else
            exit(0);
    }
}

int char_nvalid(char c)
{
    char *str;
    int i;

    str = "/*-+!@#$%^=";
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
            return (1);
        }
        i++;
    }
    return (0);
} 

int not_valid(char **strs)
{
    int i;
    int j;

    i = 0;
    while (strs[i])
    {
        j = 0;
        while (strs[i][j])
        {
            if (char_nvalid(strs[i][j]) == 1)
            {
                printf("bash: unset: `%s': not a valid identifier\n", strs[i]);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

char *ft_rm_equal(char *str)
{
	int	i;
	char *nw_str = malloc(strlen(str) + 1);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		nw_str[i] = str[i];
		i++;
	}
	nw_str[i] = '\0';
	return (nw_str);
}

void free_env(t_env *env)
{
	free(env->variable);
	free(env->value);
	free(env);
}
void ft_unset_v1(t_env **env, t_hxh *lst, int i, t_env *tmp3)
{
	t_env *tmp1;
	t_env *tmp;
	char *str;
	char *str1;

	while (*env != NULL)
    {
		str1 = ft_rm_equal(tmp3->variable);
		str = ft_rm_equal((*env)->variable);
        if (ft_strcmp(lst->value[i], str1) == 0)
        {
            tmp3 = tmp3->next;
			free_env(*env);
			*env = tmp3;
        }
        else if (ft_strcmp(lst->value[i], str) == 0)
        {
            tmp1 = (*env)->next;
			free_env(*env);
            *env = tmp;
            (*env)->next = tmp1;
        }
        tmp = (*env);
        (*env) = (*env)->next;
    }
}


void    ft_unset(t_hxh *lst, t_env **env, int *exit_status)
{
    int        i;
    t_env    *tmp;
    t_env    *tmp1;
    t_env    *tmp3;

    tmp3 = *env;
    if (ft_strcmp(lst->value[0], "unset") == 0)
    {
        if (not_valid(lst->value) == 1)
        {
            *exit_status = 1;
            return ;
        }
		else
			*exit_status = 0;
        i = 1;
        while (lst->value[i])
        {
			ft_unset_v1(env, lst, i, tmp3);
            i++;
			*env = tmp3;
        }
		printf("%p--\n", (*env)->variable);
    }
}

void    ft_putstr_fd1(char *s, int fd)
{
    int    i;

    i = 0;
    if (!s)
        return ;
    while (s[i])
    {
        if (s[i] == '\\')
            i++;
        else
        {
            ft_putchar_fd(s[i], fd);
            i++;
        }
    }
}
