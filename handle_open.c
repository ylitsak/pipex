/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:59:11 by saylital          #+#    #+#             */
/*   Updated: 2024/08/14 10:15:39 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	safe_dup2(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
	{
		ft_putendl_fd("pipex: dup2 failed", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	read_file(int *fd, char *argv[])
{
	int	fd_open;

	close(fd[0]);
	fd_open = open(argv[1], O_RDONLY);
	if (fd_open == -1)
	{
		close(fd[1]);
		ft_putstr_fd("pipex: ", 2);
		perror(argv[1]);
		exit(0);
	}
	safe_dup2(fd_open, STDIN_FILENO);
	safe_dup2(fd[1], STDOUT_FILENO);
}

void	write_file(int *fd, char *argv[])
{
	int	fd_write;

	close(fd[1]);
	fd_write = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_write == -1)
	{
		close(fd[0]);
		ft_putstr_fd("pipex: ", 2);
		perror(argv[4]);
		exit(1);
	}
	safe_dup2(fd_write, STDOUT_FILENO);
	safe_dup2(fd[0], STDIN_FILENO);
}
