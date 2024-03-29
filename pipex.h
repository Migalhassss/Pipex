/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 09:56:49 by micarrel          #+#    #+#             */
/*   Updated: 2023/07/28 09:56:49 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

char	*path_find(char *cmd, char **evnp);
void	execute(char *av, char **envp);
void	ft_error(char *msg);
void	main_process(char **av, char **envp, int *fd);
void	fork_process(char **av, char **envp, int *fd);

#endif