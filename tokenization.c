/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:25:37 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/11 15:34:09 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	g_is_in_mini;

int main(int ac, char **av, char **env)
{
	t_stack *a;
	t_hxh	*final_linked = NULL;
	t_env	*environment;
	t_main	*main_fun;
	int exit_status;
	
	(void) ac;
	(void) av;
	environment = NULL;
	main_fun = malloc(sizeof(t_main));
	filling_env(env, &environment);
	main_fun->l = NULL;
	exit_status = 0;
	main_fun->save_fd = dup(STDIN_FILENO);
	main_fun->envi2 = store_env_2darr(environment);
	setup_signal_handlers();
	while(1)
	{
		a = NULL;
		if(!isatty(STDIN_FILENO))
		{
			dup2(main_fun->save_fd, STDIN_FILENO);
			//close(save_fd);
		}
		main_fun->l = readline ("~$ :");
		add_history(main_fun->l);
		if (!main_fun->l)
		{
			printf("exit\n");
			break ;
		}
		if (main_fun->l[0] == '\0')
		{
			free(main_fun->l);
			main_fun->l = NULL;
		}
		if(main_fun->l)
		{
			if(!parentheses(main_fun->l) && !double_pipe(main_fun->l) && !ds_quotes(main_fun->l) && !ft_pars(main_fun->l))
			{
			tokenization(&a, main_fun->l);
			flaging_expandables(a);
			expanding(a, exit_status, environment);
			final_linked = ft_store(a);
			g_is_in_mini = 1;
			execution(environment, final_linked, main_fun->envi2, &exit_status);
			g_is_in_mini = 0;
			main_fun->old_path = main_fun->buf;
			main_fun->buf = ft_update_pwd(environment, main_fun->current_path, main_fun->old_path);
			}
		}
	}
}
