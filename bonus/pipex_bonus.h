/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:56:00 by micarrel          #+#    #+#             */
/*   Updated: 2023/05/14 14:56:00 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	fork_process(char *av, char **envp);
void	here_doc(char *limiter, int ac);
char	*path_find(char *cmd, char **evnp);
void	execute(char *av, char **envp);
int		open_file(char *av, int i);
void	ft_error(char *msg);

char	*protects(char *get_line);
char	*read_line(int fd, char *buffer, char *hold);
char	*get_next_line(int fd);

#endif