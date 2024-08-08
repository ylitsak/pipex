/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:08:03 by saylital          #+#    #+#             */
/*   Updated: 2024/08/08 14:29:28 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char *s, char c)
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
			break ;
		count++;
		while (*s && (in_quotes || *s != c))
		{
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

static	char	*process_word(char *s, char **dest, char c)
{
	char	*start;
	int		in_quotes;

	start = s;
	in_quotes = 0;
	while (*s && (in_quotes || *s != c))
	{
		if (*s == '\'')
		{
			in_quotes = !in_quotes;
			s++;
			continue ;
		}
		s++;
	}
	*dest = ft_substr(start, 0, s - start);
	return (s);
}

static	char	**split_words(char *s, char **arr, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (!*s)
			break ;
		s = process_word(s, &arr[i++], c);
		if (arr[i - 1] == NULL)
		{
			free_arrays(arr, i - 1);
			return (NULL);
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split_args(char *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = split_words(s, arr, c);
	if (!arr)
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
