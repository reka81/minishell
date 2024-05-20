#include "minishell.h"

char **store_env_2darr(t_env *environment)
{
    char **strs = zyalloc(1000);
    int i = 0;
    while (environment != NULL)
    {
        strs[i] = ft_strjoin(environment->variable, environment->value);
        i++;
        environment = environment->next;
    }
    strs[i] = NULL;
    return (strs);
}

char *ft_get_env(char *var, t_env *enviroment)
{
    char *new;
    while (enviroment != NULL)
    {
        new = new_var_woutequal(enviroment->variable);
        if (ft_strcmp(var, new) == 0)
        {
            // free(new);
            return (enviroment->value);
        }
        enviroment = enviroment->next;
    }
    // free(new);
    return (NULL);
}
