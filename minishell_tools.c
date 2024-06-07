/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:02:24 by mettalbi          #+#    #+#             */
/*   Updated: 2024/06/06 23:21:05 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*look_for_path(char *cmd, char *path)
{
	char	**paths;
	int		i;

	if (cmd[0] == '\0')
		return (NULL);
	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		if (access(ft_strjoin(paths[i], ft_strjoin("/", cmd)), F_OK) == 0)
		{
			return (ft_strjoin(paths[i], ft_strjoin("/", cmd)));
		}
		i++;
	}
	return ("file");
}
