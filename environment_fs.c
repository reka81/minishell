#include "minishell.h"

char **store_env_2darr(t_env *environment)
{
    char **strs = malloc(1000);
    int i = 0;
    while (environment != NULL)
    {
        strs[i] = ft_strjoin(environment->variable, ft_strjoin("=", environment->value));
        i++;
        environment = environment->next;
    }
    strs[i] = NULL;
    return (strs);
}

char *ft_get_env(char *var, t_env *enviroment)
{
    while (enviroment != NULL)
    {
        if (ft_strcmp(var, enviroment->variable) == 0)
        {
            return (enviroment->value);
        }
        enviroment = enviroment->next;
    }
    return (NULL);
}
