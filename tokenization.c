/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:25:37 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/07 18:05:47 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int	g_is_in_mini;

void	flaging_expandables(t_stack *a)
{
	while(a)
	{
		if(strcmp(a->value, "<<") == 0)
		{	
			if(a->next->type == 6)
				a->next->next->should_be_exp = 1;
			else
				a->next->should_be_exp = 0;
		}
		a = a->next;
	}
}

void tokenization(t_stack **a, char *l)
{
	int i = 0;
	int j = 0;
	char *str = NULL;
	int quote_flag = 0;
	char operator = 0;
	int flag_for_white = 0;
	
	while(l[i])
	{
		j = 0;
		str = malloc(ft_strlen1(l)+ 2);
		while(l[i] != '>' && l[i] != ' ' && l[i] != '<' && l[i] && l[i] != '|')
		{
			if(l[i] == '"')
			{
				if(j > 0)
					break;
				i++;
				while(l[i] != '"')
				{
					str[j] = l[i];
					i++;
					j++;
					quote_flag = 1;
					flag_for_white = 1;
				}
				i++;
				break;
			}
			if(l[i] == '\'')
			{
				if(j > 0)
					break;
				i++;
				while(l[i] != '\'')
				{
					str[j] = l[i];
					i++;
					j++;
					quote_flag = 2;
					flag_for_white = 1;
				}
				i++;
				break;
			}
			str[j] = l[i];
			j++;
			i++;
			flag_for_white = 1;
		}
		str[j] = '\0';
		if(str[0] == '\0')
		{
			// printf("ss\n");
			free(str);
		}
		if(flag_for_white)
		{
			// if(quote_flag != 0 || str[0]  != '$')
			// {
				// printf("%s\n", str);
				ft_lstadd_back(a, ft_lstnew(str, quote_flag));
				quote_flag = 0;
				flag_for_white = 0;
			// }
			// else
			// 	free(str);
		}
		if(l[i] == '|')
		{
			ft_lstadd_back(a, ft_lstnew(strdup("|") , 3));
			i++;
		}
		if(l[i] == ' ')
		{
			ft_lstadd_back(a, ft_lstnew(strdup(" "), 6));
			while(l[i] == ' ')
				i++;
		}
		j = 0;
		// free(str);
		if(l[i] == '>' || l[i] == '<')
		{
			str = malloc(ft_strlen1(l));
			while(l[i] == '>' || l[i] == '<')
			{
				operator = l[i];
				str[j] = operator;
				i++;
				j++;
			}
			str[j] = '\0';
			ft_lstadd_back(a, ft_lstnew(str , 3));
		}
		// free(str);
	}
}
int cmp_delim(char c)
{
	int i = 0;
	char *delim = "~!@#$%^&*-+=.?,";
	while(delim[i])
	{
		if(delim[i] == c)
			return(1);
		i++;
	}
	return(0);
}

void expanding(t_stack *a, int exit_status, t_env *environment)
{
	int i = 0;
	char *str;
	char *str2;
	int j = 0;
	int d = 0;
	int e = 0;
	int k = 0;
	int flag = 1;
	int dollar_flag = 50;
	char *user = NULL;
	int	exit_to_expand = 0;
	
	while(a)
	{
		i = 0;
		if((a->type == 1 || a->type == 0) && a->should_be_exp != 1)
		{
			str2 = malloc(100);
			str2[0] = '\0';
			while(a->value[i] != '$' && a->value[i])
			{
				str2[i] = a->value[i];
				i++;
			}
			str2[i] = '\0';
			if(a->value[i] == '$')
			{
				e = 0;
				while(a->value[i])
				{
					str = malloc(ft_strlen1(a->value) + 1);
					d = 0;
					j = ft_strlen1(str2);
					while(cmp_delim(a->value[i]))
					{
						if(a->value[i] == '?' && a->value[i - 1] == '$')
						{
							exit_to_expand = 1;
							break;
						}
						if(a->value[i] == '$')
							dollar_flag = 1;
						else
							dollar_flag = 0;
						str2[j] = a->value[i];
						j++;
						i++;
						e++;
					}
					str2[j] = '\0';
					k = ft_strlen1(str2);
					if(ft_isdigit(a->value[i]))
					{
						if(ft_isdigit(a->value[i]))	
							i++;
						free(str2);
						str2 = malloc(100);
						j = 0;
						while(a->value[i])
						{
							str2[j] = a->value[i];
							j++;
							i++;
							if(a->value[i - 1] == '$')
								break;
						}
						str2[j] = '\0';
					}
					j = 0;
					if(dollar_flag == 1)
					{	
						while(a->value[i] && !cmp_delim(a->value[i]))
						{
							str[j] = a->value[i];
							i++;
							j++;
						}
						if(a->value[i] == '?' && exit_to_expand == 1)
						{	
							str[j] = a->value[i];
							j++;
							i++;
						}
					}
					str[j] = '\0';
					if(!ft_strcmp(str , "?"))
					{
						user = ft_itoa(exit_status);
					}
					else
						user = getenv(str);
					j = ft_strlen1(str2);
					j -= 1;
					if (user)
					{
						str2[j] = '\0';
						while(user[d])
						{
							str2[j] = user[d];
							d++;
							j++;
						}
					}
					if(d > 0)	
						str2[j] = '\0';
					j = ft_strlen1(str2);
					// printf("%d--%d", j, k);
					// if(k == j)
					// {
					// 	j -= e;
					// 	str2[j] = '\0';
					// }
					while(a->value[i])
					{
						if(a->value[i] == '$')
						{
							if(a->value[i + 1])
								break;
						}
						str2[j] = a->value[i];
						i++;
						j++;
					}
					str2[j] = '\0';
					free(str);
				}
   				if (str2 != NULL)
        		{
					free(a->value);
					a->value = str2;
				}
			}
		}
		a = a->next;
	}	
}

void filling_env(char **env, t_env **environment)
{
	int i;
	int j;
	char *value;
	char *variable;
	int e;
	
	i = 0;
	while(env[i])
	{
		e = 0;
		j = 0;
		variable = malloc(strlen(env[i]) + 1);
		while(env[i][e] && env[i][e] != '=')
		{
			variable[j] = env[i][e];
			j++;
			e++;
		}
		variable[j] = '=';
		j++;
		variable[j] = '\0';
		j = 0;
		value = malloc(strlen(env[i]) + 1);
		e++;
		while(env[i][e])
		{
			value[j] = env[i][e];
			j++;
			e++;
		}
		value[j] = '\0';
		ft_lstadd_back2(environment, ft_lstnew2(variable, value));
		i++;
		
	}
}

char *ft_update_pwd(t_env *environment, char *current_path, char *old_path)
{
    while (environment != NULL)
    {
        if (strcmp("PWD", environment->variable) == 0)
        {
            current_path = getcwd(current_path, 100);
            environment->value = current_path;
        }
        if (strcmp("OLDPWD", environment->variable) == 0 && old_path != NULL)
        {
            environment->value = old_path;
        }
        environment = environment->next;
    }
    return (current_path);
}

int main(int ac, char **av, char **env)
{
	char *l;
	int count;
	t_stack *a = NULL;
	t_hxh	*final_linked = NULL;
	t_env	*environment = NULL;
	int i = 1;
	char **envi2;
	int exit_status;
	char *buf = NULL;
	char *old_path = NULL;
	char *current_path = NULL;
	
	(void) ac;
	(void) av;
	environment = NULL;
	filling_env(env, &environment);
	l = NULL;
	exit_status = 0;
	// rl_replace_line();
	int save_fd = dup(STDIN_FILENO);
	envi2 = store_env_2darr(environment);
	setup_signal_handlers();
	while(1)
	{
		a = NULL;
		if(!isatty(STDIN_FILENO))
		{
			dup2(save_fd, STDIN_FILENO);
			//close(save_fd)
		}
		l = readline ("~$ :");
		add_history(l);
		if (!l)
		{
			printf("exit\n");
			break ;
		}
		if (l[0] == '\0')
		{
			free(l);
			l = NULL;
		}
		if(l)
		{
			if(!parentheses(l) && !double_pipe(l) && !ds_quotes(l) && !ft_pars(l))
			{
			tokenization(&a, l);
			flaging_expandables(a);
			expanding(a, exit_status, environment);
			// while(a)
			// {
			// 	printf("%s----%d\n", a->value, a->type);
			// 	a = a->next;
			// }
			// exit(0);
			// printf("%s\n", environment->value);
			int i = 0;
			final_linked = ft_store(a);
			// while(final_linked)
			// {
			// 	while(final_linked->value[i])
			// 	{
			// 		printf("%s--", final_linked->value[i]);
			// 		i++;
			// 	}
			// 	printf("\n");
			// 	final_linked = final_linked->next;
			// }
			// exit(0);
			// char * hh = look_for_path(final_linked->value[0], getenv("PATH"));
			// printf("%s", hh);
			// exit(1);
			g_is_in_mini = 1;
			execution(environment, final_linked, envi2, &exit_status);
			g_is_in_mini = 0;
			old_path = buf;
			buf = ft_update_pwd(environment, current_path, old_path);
			// printf("%d\n", exit_status);
			}
		}
	}
}
