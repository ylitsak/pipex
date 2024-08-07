/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:07:53 by saylital          #+#    #+#             */
/*   Updated: 2024/08/07 10:36:52 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_status(void)
{
	int	status1;
	int	status2;

	waitpid(-1, &status1, 0);
	waitpid(-1, &status2, 0);
	status1 = status1 >> 8;
	status2 = status2 >> 8;
	if (status1 != 0 && status1 > status2)
	{
		exit(status1);
	}
	exit(status2);
}

static void	pipex(char *argv[], char *envp[])
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		read_file(fd, argv);
		first_child(argv, envp);
	}
	pid2 = fork();
	if (pid2 == -1)
		exit(EXIT_FAILURE);
	if (pid2 == 0)
	{
		write_file(fd, argv);
		second_child(argv, envp);
	}
	close(fd[0]);
	close(fd[1]);
	check_status();
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		ft_putendl_fd("pipex: Error: expected 4 arguments", 2);
		return (1);
	}
	pipex(argv, envp);
	return (0);
}
