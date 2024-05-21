/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ll3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaheddac <zaheddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:28:45 by mettalbi          #+#    #+#             */
/*   Updated: 2024/05/21 15:22:12 by zaheddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	count_strings(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static void	*ft_free(char **strs, int i)
{
	while (i--)
		free(strs[i]);
	free(strs);
	return (NULL);
}

static	char	**fill_words(char **str, const char *s, char c, int count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[j] && i < count)
	{
		len = 0;
		while (s[j] == c && s[j])
			j++;
		while (s[j + len] != c && s[j + len])
			len++;
		if (len != 0)
		{
			str[i] = zyalloc((len + 1) * sizeof(char));
			if (!str[i])
				return (ft_free(str, i));
			ft_strlcpy(str[i], (s + j), len + 1);
			j = j + len;
			i++;
		}
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	str = NULL;
	str = zyalloc((count_strings(s, c) + 1) * 200 * sizeof(char *));
	if (!str)
		return (NULL);
	if (!s)
	{
		*str = NULL;
		return (str);
	}
	return (fill_words(str, s, c, count_strings(s, c)));
}
