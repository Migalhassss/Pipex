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

char	*clean_return(char *path, char **paths)
{
	free_paths(paths);
	return (path);
}

char	*path_find(char *cmd, char **evnp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (ft_strnstr(evnp[i], "PATH", 4) == 0)
		i++;
	path = ft_substr(evnp[i], 5, ft_strlen(evnp[i]));
	paths = ft_split(path, ':');
	free (path);
	i = 0;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (clean_return(path, paths));
		free(path);
	}
	free_paths(paths);
	return (0);
}

void	execute(char *av, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, ' ');
	path = path_find(cmd[0], envp);
	if (!path)
	{
		free_paths(cmd);
		ft_error("Error command not found\n");
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_paths(cmd);
		free(path);
		ft_error("Error to execute execve");
	}
}
