/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 09:58:35 by micarrel          #+#    #+#             */
/*   Updated: 2023/07/28 09:58:35 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*path_find(char *cmd, char **evnp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	i = 0;
	while (ft_strnstr(evnp[i], "PATH", 4) == 0)
		i++;
	path = ft_substr(evnp[i], 5, ft_strlen(evnp[i]));
	paths = ft_split(path, ':');
	free (path);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_paths(paths);
	return (0);
}

void	execute(char *av, char **envp)
{
	int		i;
	char	*path;
	char	**cmd;

	i = 0;
	cmd = ft_split(av, ' ');
	path = path_find(cmd[0], envp);
	if (!path)
	{
		while (cmd[i])
		{
			free (cmd[i]);
			i++;
		}
		free(cmd);
		ft_error("Error path");
	}
	if (execve(path, cmd, envp) == -1)
		ft_error("Error to execute execve");
}
