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

char	*clean_return(char *path, char **paths)
{
	free_paths(paths);
	return (path);
}

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
		close(fd[0]);
	}
}

void	here_doc(char *limiter, int ac)
{
	pid_t	id;
	int		fd[2];
	char	*line;

	line = NULL;
	if (ac < 6 || pipe(fd) == -1)
		ft_error("Error\n");
	id = fork();
	if (id == -1)
		ft_error("Error creating fork\n");
	if (id == 0)
	{
		close(fd[0]);
		line = get_next_line(0);
		aux2(fd, line, limiter);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

void	last_fork(int fileout, char **av, int ac, char **envp)
{
	int	id;
	int	i;

	i = 0;
	id = fork();
	if (id == 0)
	{
		dup2(fileout, STDOUT_FILENO);
		execute(av[ac - 2], envp);
	}
	else if (id < 0)
		ft_printf("Error: Failed to fork process\n");
	else
		while (i++ < ac - 3)
			waitpid(-1, NULL, 0);

}

void	close_files(int filein, int fileout, char *here_doc)
{
	if (ft_strncmp(here_doc, "here_doc", 8) != 0)
		close(filein);
	close(fileout);
	exit(1);
}

int	main(int ac, char **av, char **envp)
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
			if (fileout == -1)
				exit(1);
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			fileout = open_file(av[ac - 1], 1);
			filein = open_file(av[1], 2);
			if (fileout == -1 || filein == -1)
				close_files(filein, fileout, NULL);
			dup2(filein, STDIN_FILENO);
		}
		while (i < ac - 2)
			fork_process(av[i++], envp);
		last_fork(fileout, av, ac, envp);
		ft_printf("Error: Failed to fork process\n");
		close_files(filein, fileout, av[1]);
	}
	else
		ft_printf("Error arguments\n");
}
