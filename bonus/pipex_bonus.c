/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:56:03 by micarrel          #+#    #+#             */
/*   Updated: 2023/05/14 14:56:03 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "pipex_bonus.h"

void	fork_process(char *av, char **envp)
{
	pid_t	id;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("Error creating pipe\n");
	id = fork();
	if (id == -1)
		ft_error("Error creating fork\n");
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execute(av, envp);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(id, NULL, 0);
	}
}

void	here_doc(char *limiter, int ac)
{
	pid_t	id;
	int		fd[2];
	char	*line;

	line = NULL;
	if (ac < 6)
		ft_error("Error\n");
	if (pipe(fd) == -1)
		ft_error("Error creating pipe (here_doc)\n");
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		line = get_next_line(0);
		while (line)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				exit(0);
				free(line);
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int main(int ac, char **av, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(av[ac - 1], 0);
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			fileout = open_file(av[ac - 1], 1);
			filein = open_file(av[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < ac - 2)
			fork_process(av[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute (av[ac - 2], envp);
	}
	else
		ft_printf("Error in arguments\n");
}