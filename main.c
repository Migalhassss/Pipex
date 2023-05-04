#include "pipex.h"

void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
}

void	fork_process(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		ft_error("Error opening file in fork function\n");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute(av[2], envp);
}

void	main_process(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		ft_error("Error opening file in main function\n");
	dup2(fd[0], STDIN_FILENO);
	dup2(infile, STDOUT_FILENO);
	close(fd[1]);
	execute(av[3], envp);
}

int main (int ac, char **av, char **envp)
{
	int	fd[2];
	pid_t	id;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			ft_error("Error creating pipe\n");
		id = fork();
		if (id == -1)
			ft_error("Error creating fork\n");
		if (id == 0)
			fork_process(av, envp, fd);
		waitpid(id, NULL, 0);
		main_process(av, envp, fd);
	}
	else
		ft_printf("Error in arguments\n");
	// Ex: ./pipex file1 cmd1 cmd2 file2
}