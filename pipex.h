/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:08:49 by saylital          #+#    #+#             */
/*   Updated: 2024/08/07 13:43:55 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

void	first_child(char *argv[], char *envp[]);
void	second_child(char *argv[], char *envp[]);
char	*find_executable_path(char *cmd_args, char *envp[]);
char	*find_path(char *cmd, char *envp[]);
void	free_all(char **free_dir);
char	*rmv_last_arg_ifspace(char *str, char limiter);
char	*is_space_string(char *str);
void	read_file(int *fd, char *argv[]);
void	write_file(int *fd, char *argv[]);
void	check_permission1(char *exec, char *envp[], char *argv[]);
void	check_permission2(char *exec, char *envp[], char *argv[]);
void	execute_first(char *argv[], char *firstpath, char *envp[]);
void	execute_second(char *argv[], char *secondpath, char *envp[]);
int		is_command(char *str);
char	*parse_quotes(char *str);
char	**ft_split_args(char *s);
int		skip_quotes(char *str, char quote, int i);
char	**remove_quotes(char **arr);

#endif