/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:06:34 by saylital          #+#    #+#             */
/*   Updated: 2024/08/08 14:56:15 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_error(void)
{
	ft_putendl_fd("Pipe error: failed to create pipe", 2);
	exit(EXIT_FAILURE);
}

void	fork_error(int *fd)
{
	ft_putendl_fd("Fork error: forking failed", 2);
	close(fd[0]);
	close(fd[1]);
	exit(EXIT_FAILURE);
}
