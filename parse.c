/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:14:48 by saylital          #+#    #+#             */
/*   Updated: 2024/08/07 14:00:21 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	skip_word(char *string, int i)
{
	while (string[i] && string[i] != ' ')
	{
		if (string[i] && (string[i] == '"' || string[i] == '\''))
		{
			i = skip_quotes(string, string[i], i);
			if (i == -1)
				return (-1);
		}
		else
			i++;
	}
	return (i);
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

static int	word_counter(char *string)
{
	size_t	count_words;
	int		i;

	count_words = 0;
	i = 0;
	while (string[i])
	{
		while (string[i] && string[i] == ' ')
			i++;
		if (string[i])
			count_words++;
		i = skip_word(string, i);
		if (i == -1)
			return (-1);
	}
	return (count_words);
}

static char	**word_splitter(char *s, char **ptrarray, int i)
{
	size_t		j;
	size_t		start;
	size_t		len;

	j = 0;
	while (s[j])
	{
		while (s[j] && s[j] == ' ')
			j++;
		if (s[j] == '\0')
			break ;
		start = j;
		j = skip_word(s, j);
		len = j - start;
		ptrarray[i] = ft_substr(s, start, len);
		if (ptrarray[i] == NULL)
		{
			free_arrays(ptrarray, i);
			return (NULL);
		}
		i++;
	}
	ptrarray[i] = NULL;
	return (ptrarray);
}

char	**ft_split_args(char *s)
{
	int			total_words;
	char		**word_array;

	if (!s)
		return (NULL);
	total_words = word_counter(s);
	if (total_words == -1)
		return (NULL);
	word_array = malloc((total_words + 1) * sizeof(char *));
	if (!word_array)
		return (NULL);
	word_array = word_splitter(s, word_array, 0);
	word_array = remove_quotes(word_array);
	return (word_array);
}
