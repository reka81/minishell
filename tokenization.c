/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:25:37 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/20 15:36:43 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_is_in_mini;

void ft_rm_null(t_stack **a)
{
    int i;
    t_stack *tmp1;
	t_stack *tmp2;
	t_stack *tmp;
    i = 0;
	tmp2 = *a;
    while ((*a) != NULL)
    {
		if ((*a)->value == NULL && i == 0)
		{
			tmp2 = (*a)->next;
			free((*a)->value);
			free(*a);
			(*a) = tmp2;
		}
		else if ((*a)->value == NULL && (*a)->next != NULL)
        {
            tmp1 = (*a)->next;
			free((*a)->value);
			free(*a);
			(*a) = tmp;
			(*a)->next = tmp1;
        }
        else if ((*a)->value == NULL && (*a)->next == NULL)
        {
           tmp->next = NULL;
        }
        tmp = *a;
		if(*a)
			*a = (*a)->next;
		i++;
    }
	*a = tmp2;
}
int check_if_null(t_stack *a)
{
	while(a)
	{
		if(a->value == NULL)
			return(1);
		a = a->next;
	}
	return(0);
}
void freeing_pr(t_stack **a)
{
	free((*a)->value);
	free(*a);
	*a = NULL;
}

void clean_final(t_hxh **final_linked)
{
    int i;
    t_hxh *tmp;
    t_hxh *tmp1;
    t_hxh *tmp2;

    i = 0;
    tmp2 = *final_linked;
    while (*final_linked)
    {
        if ((*final_linked)->is_faulty == 2 || (*final_linked)->ambigious)
        {
            if(i == 0)
            {
                tmp2 = (*final_linked)->next;
                free(*final_linked);
                *final_linked = tmp2;
            }
            else if ((*final_linked)->next != NULL)
            {
                tmp1 = (*final_linked)->next;
                free(*final_linked);
                (*final_linked) = tmp;
                (*final_linked)->next = tmp1;
            }
            else if ((*final_linked)->next == NULL)
            {
                tmp->next = NULL;
            }
        }
        tmp = *final_linked;
        if (*final_linked)
            *final_linked = (*final_linked)->next;
        i++;
    }
    *final_linked = tmp2;
}

int check_if_faulty(t_hxh *a)
{
    while(a)
    {
        if(a->is_faulty == 2 || a->ambigious == 20)
            return(1);
        a = a->next;
    }
    return(0);
}

void	rest_of_main(t_main *main_fun, t_stack *a
			, t_env **environment, t_hxh *final_linked)
{
	if (main_fun->l[0] == '\0')
	{
		free(main_fun->l);
		main_fun->l = NULL;
	}
	if (main_fun->l)
	{
		if (!parentheses(main_fun->l) && !double_pipe(main_fun->l)
			&& !ds_quotes(main_fun->l) && !ft_pars(main_fun->l))
		{
			tokenization(&a, main_fun->l);
			flaging_expandables(a);
			expanding(a, main_fun->exit_status, *environment);
			while(check_if_null(a))
				ft_rm_null(&a);
			if(a)
			{	
				if(a->type == 6 && a->next == NULL)
					freeing_pr(&a);
			}
			if(a)
			{
				final_linked = ft_store(a);
				while(check_if_faulty(final_linked))    
					clean_final(&final_linked);
				if(final_linked)
				{
					g_is_in_mini = 1;
					execution(environment, final_linked,
						main_fun->envi2, &main_fun->exit_status);
					g_is_in_mini = 0;
					main_fun->old_path = main_fun->buf;
					main_fun->buf = ft_update_pwd(*environment,
						main_fun->current_path, main_fun->old_path);
				}
			}
		}
	}
}

t_env    *ft_lstnew5(char *variable, char *value)
{
    t_env    *s1;

    s1 = malloc(sizeof(t_env));
    if (!s1)
        return (NULL);
    s1->variable = variable;
    s1->value = value;
    s1->next = NULL;
    return (s1);
}

void	routine(t_stack *a, t_main *main_fun, t_env **environment,
			t_hxh *final_linked)
{
	while (1)
	{
		a = NULL;
		if (!isatty(STDIN_FILENO))
		{
			dup2(main_fun->save_fd, STDIN_FILENO);
			close(main_fun->save_fd);
		}
		main_fun->l = readline ("~$ :");
		add_history(main_fun->l);
		if (!main_fun->l)
		{
			printf("exit\n");
			break ;
		}
		rest_of_main(main_fun, a, environment, final_linked);
	}
}

void    ft_lstadd_back7(t_env **lst, t_env *newnode)
{
    t_env    *start;

    if (!lst)
        return ;
    start = *lst;
    if (*lst)
    {
        while (start->next)
            start = start->next;
        start->next = newnode;
    }
    else
        *lst = newnode;
}

char *fill(char *str1, char *str2)
{
    int i = 0;
    str1 = malloc(sizeof(char) * strlen(str2) + 1);
    while (str2[i])
    {
        str1[i] = str2[i];
        i++;
    }
    str1[i] = '\0';
    return (str1);
}

void fill_env2(t_env **environment)
{
    int i = 0;
    *environment = NULL;
    char *value = malloc(50);
    char *variable;
    while (i < 4)
    {
        if (i == 0)
        {
            variable = fill(variable ,"PWD=");
            getcwd(value, 50);
            ft_lstadd_back7(environment, ft_lstnew5(variable, value));
        }
        if (i == 1)
        {
            variable = fill(variable, "SHLVL=");
            value = fill(value, "1");
            ft_lstadd_back7(environment, ft_lstnew5(variable, value));
        }
        if (i == 2)
        {
            variable = fill(variable, "_=");
            value = fill(value, "/usr/bin/env");
            ft_lstadd_back7(environment, ft_lstnew5(variable, value));
        }
        if (i == 3)
        {
            variable = fill(variable, "PATH=");
            value = fill(value, "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
            ft_lstadd_back7(environment, ft_lstnew5(variable, value));
        }
        i++;
    }
}

int	main(int ac, char **av, char **env)
{
	t_stack	*a;
	t_hxh	*final_linked;
	t_env	*environment;
	t_main	*main_fun;

	a = NULL;
	final_linked = NULL;
	(void) ac;
	(void) av;
	environment = NULL;
	main_fun = malloc(sizeof(t_main));
	filling_env(env, &environment);
	if(!environment)
		fill_env2(&environment);
	main_fun->l = NULL;
	main_fun->exit_status = 0;
	main_fun->save_fd = dup(STDIN_FILENO);
	main_fun->envi2 = store_env_2darr(environment);
	setup_signal_handlers();
	routine(a, main_fun, &environment, final_linked);
}
