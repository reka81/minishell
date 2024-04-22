#include "minishell.h"

char	*look_for_path(char *cmd, char *path)
{
	char **paths;
	int i = 0;
	paths = ft_split(path, ':');
	while(paths[i])
	{
		if(access(ft_strjoin(paths[i], ft_strjoin("/", cmd)), F_OK) == 0)
			return(ft_strjoin(paths[i], ft_strjoin("/", cmd)));
		i++;
	}
	return("file not found");
}