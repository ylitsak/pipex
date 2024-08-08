/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:09:13 by saylital          #+#    #+#             */
/*   Updated: 2024/08/08 15:02:25 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(char **free_dir)
{
	int	i;

	i = 0;
	while (free_dir[i])
	{
		free(free_dir[i]);
		i++;
	}
	free(free_dir);
}

char	*parse_quotes(char *str)
{
	int		i;
	int		j;
	char	*parsed;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 39)
			j++;
		i++;
	}
	parsed = malloc((j + 1) * sizeof(char));
	if (parsed == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != 39)
			parsed[j++] = str[i];
		i++;
	}
	parsed[j] = '\0';
	return (parsed);
}

char	*rmv_last_arg_ifspace(char *str, char limiter)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] && str[i] != limiter)
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != limiter)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*is_space_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

int	is_command(char *str)
{
	if (ft_strncmp(str, "command", 7) == 0 && *str + 8 == '\0')
	{
		ft_putendl_fd("pipex: redirection with no command", 2);
		return (1);
	}
	return (0);
}
