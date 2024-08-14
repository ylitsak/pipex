/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:07:35 by saylital          #+#    #+#             */
/*   Updated: 2024/08/13 21:25:44 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char *envp[])
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (path == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		return (NULL);
	}
	return (path);
}

char	*find_directory(char **dir, char *splitted_args)
{
	int		i;
	char	*executable_path;
	char	*slash;

	i = 0;
	while (dir[i] != NULL)
	{
		slash = ft_strjoin(dir[i], "/");
		executable_path = ft_strjoin(slash, splitted_args);
		free(slash);
		if (access(executable_path, F_OK) == 0)
		{
			if (access(executable_path, X_OK) == 0)
				return (executable_path);
			ft_putendl_fd("pipex: permission denied:", 2);
			free(executable_path);
			exit(126);
		}
		free(executable_path);
		i++;
	}
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(splitted_args, 2);
	return (NULL);
}

char	*find_executable_path(char *cmd_args, char *envp[])
{
	char	*get_path;
	char	**path_directory;
	char	**args_split;
	char	*found_path;

	get_path = find_path(cmd_args, envp);
	if (get_path == NULL)
		return (NULL);
	args_split = ft_split(cmd_args, ' ');
	path_directory = ft_split(get_path, ':');
	if (path_directory == NULL)
	{
		free_all(args_split);
		return (NULL);
	}
	found_path = find_directory(path_directory, args_split[0]);
	free(cmd_args);
	free_all(args_split);
	free_all(path_directory);
	return (found_path);
}
