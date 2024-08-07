/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:38:40 by saylital          #+#    #+#             */
/*   Updated: 2024/08/07 13:59:05 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	skip_quotes(char *str, char quote, int i)
{
	if (str[i + 1])
		i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	else
		return (-1);
	return (i);
}

static	int	count_quotes(char *str)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			j = i;
			i = skip_quotes(str, str[i], i);
			count = count + (i - j - 2);
		}
		if (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
			count++;
		i++;
	}
	return (count);
}

static	char	*handle_quotes(char *str, int i)
{
	int		j;
	int		k;
	char	*dest;

	k = count_quotes(str);
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	k = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			j = i + 1;
			i = skip_quotes(str, str[i], i);
			while (j < i - 1)
				dest[k++] = str[j++];
		}
		if (str[i] && str[i] != '"' && str[i] != '\'')
			dest[k++] = str[i++];
	}
	dest[k] = '\0';
	free(str);
	return (dest);
}

char	**remove_quotes(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if ((ft_strchr(arr[i], '"')) || (ft_strchr(arr[i], '\'')))
			arr[i] = handle_quotes(arr[i], 0);
		i++;
	}
	return (arr);
}
