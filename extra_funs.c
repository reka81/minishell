/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_funs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:29:19 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/14 17:32:27 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	charing(char **str, char **str1, t_env **env, t_env *tmp3)
{
	*str1 = ft_rm_equal(tmp3->variable);
	*str = ft_rm_equal((*env)->variable);
}

void	initing_values(t_int *lor_int, char **var, t_stack **lst)
{
	(1) && (lor_int->val = NULL, *var = NULL, lor_int->chen = NULL);
	lor_int->chen = rederection_handling(lst, lor_int, lor_int->chen);
}

void	rest_of_main7(t_stack **a, t_main *main_fun, t_env **environment)
{
	flaging_expandables(*a);
	expanding(*a, main_fun->exit_status, *environment);
	print_ambigious(*a);
	while (check_if_null(*a))
		ft_rm_null(a);
}
