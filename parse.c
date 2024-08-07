/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:14:48 by saylital          #+#    #+#             */
/*   Updated: 2024/08/07 11:27:17 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int skip_quotes(char *str, char quote, int i)
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
	char	quote;
	int		i;

	count_words = 0;
	i = 0;
	while (string[i])
	{
		while (string[i] && string[i] == ' ')
			i++;
		if (string[i])
			count_words++;
		while (string[i] && string[i] != ' ')
		{
			if (string[i] && (string[i] == '"' || string[i] == '\''))
			{
				quote = string[i];
				i = skip_quotes(string, quote, i);
			}
			else
				i++;
		}
	}
	return (count_words);
}
static char	**word_splitter(char *s, char **ptrarray)
{
	size_t		i;
	size_t		j;
	size_t		start;
	size_t		len;
	char		quote;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] && s[j] == ' ')
			j++;
		if (s[j] == '\0')
			break ;
		start = j;
		while (s[j] && s[j] != ' ')
		{
			if (s[j] && (s[j] == '"' || s[j] == '\''))
			{
				quote = s[j];
				j = skip_quotes(s, quote, j);
			}
			else
				j++;
		}
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

// static void print_array(char **arr)
// {
// 	int i = 0;
// 	while (arr[i])
// 	{
// 		ft_putendl_fd(arr[i], 2);
// 		i++;
// 	}
// }

char	**ft_split_args(char *s)
{
	int			total_words;
	char		**word_array;

	if (!s)
		return (NULL);
	total_words = word_counter(s);
	word_array = malloc((total_words + 1) * sizeof(char *));
	if (word_array == NULL)
		return (NULL);
	word_array = word_splitter(s, word_array);
	// print_array(word_array);
	return (word_array);
}
