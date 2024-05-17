/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:45:18 by zaheddac          #+#    #+#             */
/*   Updated: 2024/05/16 19:41:01 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_fun(char *str)
{
	int i = 0;
	
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			i++;
			while (str[i] != '\0')
			{
				if (str[i] != ' ')
					return (0);
				i++;
			}
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}		
	return (0);
}

int ft_parc1(char *str, int len)
{
	if (str[0] == '|')
    {
        printf("bash: syntax error\n");
        return (1);
    }
    else if (str[len] == '>' || str[len] == '<'|| str[len] == '|' || check_fun(str) == 1)
    {
        printf("bash: syntax error\n");
        return (1);
    }
	return (0);
}

int ft_pars(char *str)
{
    int len;
    int i;
    
    len = strlen(str) - 1;
    if (len < 0)
        len  = 0;
    if(str[0] == ' ')
    {
        i = 0;
        while(str[i] == ' ')
        {
            if(str[i + 1] == '|')
            {    
                printf("bash: syntax error\n");
                return (1);
            }
            i++;
        }
    }
	if (ft_parc1(str, len) == 1)
		return (1);
    return (0);
}

void search_sq(char *str, int *i)
{
	(*i)++;
	 while (str[*i] != '\'' && str[*i])
		(*i)++;
}

void search_dq(char *str, int *i)
{
	(*i)++;
	while (str[*i] != '\"' && str[*i])
    	(*i)++;
}

int ds_quotes(char *str)
{
    int i = -1;
    
    while (str[++i])
    {
        if (str[i] == '\'')    
        {
			search_sq(str, &i);
            if (str[i] != '\'')
            {
                printf("bash: syntax error\n");
                return(1);
            }
        }
        else if (str[i] == '\"')    
        {
			search_dq(str, &i);
            if (str[i] != '\"')
            {
                printf("bash: syntax error\n");
                return (1);
            }
        }
    }
    return(0);
}

int pipeee(char *str, int *i, int *j)
{
	if(i - 1 >= 0)
    {
		if(str[*i - 1]  == '|' || str[*i + 1] == '|')
    	{    
        	printf("bash: syntax error\n");
        	return(1);       
    	}
    	*j = *i + 1;
    	if (str[*j] == ' ')
    	{
        	while(str[*j] && str[*j] == ' ')
        	{
            	if(str[*j + 1] == '|')
            	{ 
                	printf("bash: syntax error\n");
                	return(1);
            	}
            	(*j)++;
        	}
    	}
	}
	return (0);
}
int infileee(char *str, int *i, int *j)
{
	if(str[*i + 1] == '>')
    {
        printf("bash: syntax error\n");
        return(1);
    }
    if(*i >= 2)
	{	
		if((str[*i - 1]  == '<' && str[*i - 2] == '<')|| (str[*i + 1] == '<' && str[*i + 2] == '<'))
        {
        	printf("bash: syntax error\n");
            return(1);       
        }
	}
	*j = *i + 1;
    if(str[*j] == ' ')
    {
		while(str[*j] && str[*j] == ' ')
        {
            if(str[*j + 1] == '<' || str[*j + 1] == '>')
            {
                printf("bash: syntax error\n");
                return(1);
            }
            (*j)++;
        }
    }
	return (0);
}
int rederectionnn(char *str, int *i, int *j)
{
	if(str[*i + 1] == '<')
    {
        printf("bash: syntax error\n");
        return(1);
    }
    if(*i >= 2)
	{	
		if((str[*i - 1]  == '>' && str[*i - 2] == '>')|| (str[*i + 1] == '>' && str[*i + 2] == '>'))
        {
            printf("bash: syntax error\n");
            return(1);       
        }
	}
	*j = *i + 1;
    if(str[*j] == ' ')
    {
        while(str[*j] && str[*j] == ' ')
        {
            if(str[*j + 1] == '>' || str[*j + 1] == '<')
            {
                printf("bash: syntax error\n");
                return(1);
            }
            (*j)++;
        }
    }
	return (0);
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
			if (pipeee(str, &i, &j) == 1)
				return (1);
        }
        else if (str[i] == '>')
        {
			if (rederectionnn(str, &i, &j) == 1)
				return (1);
        }
        else if (str[i] == '<')
        {
			if (infileee(str, &i, &j) == 1)
				return (1);
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
