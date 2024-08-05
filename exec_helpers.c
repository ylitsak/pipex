/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:15:10 by saylital          #+#    #+#             */
/*   Updated: 2024/08/02 09:39:07 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_dir(char *str)
{
	int		fd3;

	fd3 = open(str, O_DIRECTORY);
	if (fd3 != -1)
	{
		close(fd3);
		return (1);
	}
	return (0);
}

void	check_permission1(char *exec, char *envp[], char *argv[])
{
	if (access(exec, F_OK) == 0)
	{
		if (access(exec, X_OK) == 0 && !is_dir(exec))
			execute_first(argv, exec, envp);
		else
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putstr_fd(exec, 2);
			ft_putstr_fd("\n", 2);
			free(exec);
			exit(0);
		}
	}
	else
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putstr_fd(exec, 2);
		ft_putstr_fd("\n", 2);
		free(exec);
		exit(0);
	}
}

void	check_permission2(char *exec, char *envp[], char *argv[])
{
	if (access(exec, F_OK) == 0)
	{
		if (access(exec, X_OK) == 0 && !is_dir(exec))
			execute_second(argv, exec, envp);
		else
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putstr_fd(exec, 2);
			ft_putstr_fd("\n", 2);
			free(exec);
			exit(126);
		}
	}
	else
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putstr_fd(exec, 2);
		ft_putstr_fd("\n", 2);
		free(exec);
		exit(127);
	}
}
