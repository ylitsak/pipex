/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:43:45 by saylital          #+#    #+#             */
/*   Updated: 2024/08/07 15:11:39 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_first(char *argv[], char *firstpath, char *envp[])
{
	char	**cmd_parse;

	cmd_parse = ft_split_args(argv[2]);
	{
		free(firstpath);
		ft_putendl_fd("pipex: Error: Malloc fail", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(firstpath, cmd_parse, envp) == -1)
	{
		perror("pipex: ");
		free(firstpath);
		free_all(cmd_parse);
		exit(0);
	}
}

void	execute_second(char *argv[], char *secondpath, char *envp[])
{
	char	**cmd_parse1;

	cmd_parse1 = ft_split_args(argv[3]);
	if (!cmd_parse1)
	{
		free(secondpath);
		ft_putendl_fd("pipex: Error: Malloc fail", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(secondpath, cmd_parse1, envp) == -1)
	{
		perror("pipex: ");
		free(secondpath);
		free_all(cmd_parse1);
		exit(126);
	}
}

void	first_child(char *argv[], char *envp[])
{
	char	*full_path;

	if (*argv[2] == 0)
	{
		ft_putendl_fd("pipex: permission denied: ", 2);
		exit(0);
	}
	if (is_command(argv[2]) == 1)
		exit (0);
	full_path = is_space_string(argv[2]);
	if (full_path == NULL)
	{
		ft_putendl_fd("pipex: command not found: ", 2);
		exit(0);
	}
	full_path = rmv_last_arg_ifspace(full_path, ' ');
	if (ft_strchr(full_path, '/'))
		check_permission1(full_path, envp, argv);
	full_path = find_executable_path(full_path, envp);
	if (full_path == NULL)
		exit(0);
	execute_first(argv, full_path, envp);
}

void	second_child(char *argv[], char *envp[])
{
	char	*exec_path;

	if (*argv[3] == 0)
	{
		ft_putendl_fd("pipex: permission denied: ", 2);
		exit(126);
	}
	if (is_command(argv[3]) == 1)
		exit (1);
	exec_path = is_space_string(argv[3]);
	if (exec_path == NULL)
	{
		ft_putendl_fd("pipex: command not found: ", 2);
		exit(127);
	}
	exec_path = rmv_last_arg_ifspace(exec_path, ' ');
	if (ft_strchr(exec_path, '/'))
		check_permission2(exec_path, envp, argv);
	exec_path = find_executable_path(exec_path, envp);
	if (exec_path == NULL)
		exit(127);
	execute_second(argv, exec_path, envp);
}
