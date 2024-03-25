/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:45:18 by zaheddac          #+#    #+#             */
/*   Updated: 2024/03/24 21:49:30 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pars(char *str)
{
    int len = strlen(str) - 1;
    int i;

    if(str[0] == ' ')
    {
        i = 0;
        while(str[i] == ' ')
        {
            if(str[i + 1] == '|')
            {    
                printf("bash: syntax error\n");
                return(1);
            }
            i++;
        }
    }
    if (str[0] == '|')
    {
        printf("bash: syntax error\n");
        return (1);
    }
    else if (str[len] == '>' || str[len] == '<'|| str[len] == '|')
    {
        printf("bash: syntax error\n");
        return(1);
    }
    return (0);
}

int ds_quotes(char *str)
{
    int i = 0;
    
    while (str[i])
    {
        if (str[i] == '\'')    
        {
            i++;
            while (str[i] != '\'' && str[i])
                i++;
            if (str[i] != '\'')
            {
                printf("bash: syntax error\n");
                return(1);
            }
        }
        else if (str[i] == '\"')    
        {
            i++;
            while (str[i] != '\"' && str[i])
                i++;
            if (str[i] != '\"')
            {
                printf("bash: syntax error\n");
                return (1);
            }
        }
        else if (str[i] == '(')    
        {
            i++;
            while (str[i] != ')' && str[i])
                i++;
            if (str[i] != ')')
            {
                printf("bash: syntax error\n");
                return (1);
            }
        }
        i++;
    }
    return(0);
}
int double_pipe(char *str)
{
    int i = 0;
    int j  = 0;
    int count = 0;
    int count1 = 0; 
    while (str[i])
    {
        if(str[i] == '|')
        {
            if(i - 1 >= 0)
            {
                if(str[i - 1]  == '|' || str[i + 1] == '|')
                {    
                    printf("bash: syntax error\n");
                    return(1);       
                }
                j = i + 1;
                if(str[j] == ' ')
                {
                    while(str[j] && str[j] == ' ')
                    {
                        if(str[j + 1] == '|')
                        {
                            printf("bash: syntax error\n");
                            return(1);
                        }
                        j++;
                    }
                }
            }
        }
        else if (str[i] == '>')
        {
            if(i == 0)
            {
                printf("bash: syntax error\n");
                return(1);
            }
            if(str[i + 1] == '<')
            {
                printf("bash: syntax error\n");
                return(1);
            }
            if((str[i - 1]  == '>' && str[i - 2] == '>')|| (str[i + 1] == '>' && str[i + 2] == '>'))
            {
                printf("bash: syntax error\n");
                return(1);       
            }
            j = i + 1;
            if(str[j] == ' ')
            {
                while(str[j] && str[j] == ' ')
                {
                    if(str[j + 1] == '>' || str[j + 1] == '<')
                    {
                        printf("bash: syntax error\n");
                        return(1);
                    }
                    j++;
                }
            }
        }
        else if (str[i] == '<')
        {
            if(str[i + 1] == '>')
            {
                printf("bash: syntax error\n");
                return(1);
            }
            if((str[i - 1]  == '<' && str[i - 2] == '<')|| (str[i + 1] == '<' && str[i + 2] == '<'))
            {
                printf("bash: syntax error\n");
                return(1);       
            }
            j = i + 1;
            if(str[j] == ' ')
            {
                while(str[j] && str[j] == ' ')
                {
                    if(str[j + 1] == '<' || str[j + 1] == '>')
                    {
                        printf("bash: syntax error\n");
                        return(1);
                    }
                    j++;
                }
            }
        }
        i++;
    }
    return(0);
}
int parentheses(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '(')
        {
            while (str[i] != '|' && str[i])
                i++;
            i--;
            while (str[i] == ' ')
                i--;
            if (str[i] != ')')
            {
                printf("bash: syntax error\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}
