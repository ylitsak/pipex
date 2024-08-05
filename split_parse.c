/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:08:03 by saylital          #+#    #+#             */
/*   Updated: 2024/08/05 23:57:58 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*s)
	{
		while (*s == c && !in_quotes && *s != '\0')
			s++;
		if (*s == '\0')
			break;
		count++;
		while (*s && (in_quotes || *s != c))
		{
			if (*s == '\\' && *(s + 1))
			{
				s += 2;
				continue;
			}
			if (*s == '\'')
				in_quotes = !in_quotes;
			s++;
		}
	}
	return (count);
}
static void	free_arrays(char **words, size_t n)
{
	while (n > 0)
	{
		n--;
		free(words[n]);
	}
	free(words);
}

static	char	**split_words(char const *s, char **arr, char c)
{
	int			i;
	const char	*start;
	int			in_quotes;

	i = 0;
	in_quotes = 0;
	while (*s)
	{
		while (*s == c && !in_quotes && *s != '\0')
			s++;
		if (!*s)
			break;
		start = s;
		while (*s && (in_quotes || *s != c))
		{
			if (*s == '\\' && *(s + 1))
			{
				s += 2;
				continue;
			}
			if (*s == '\'')
			{
				in_quotes = !in_quotes;
				s++;
				continue;
			}
			s++;
		}
		arr[i] = ft_substr(start, 0, s - start);
		if (arr[i] == NULL)
		{
			free_arrays(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split_args(char const *s, char c)
{
	char **arr;
	int words;

	if (!s) return NULL;
	words = count_words(s, c);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr) return NULL;
	if (!split_words(s, arr, c))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
