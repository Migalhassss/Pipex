/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:02:06 by micarrel          #+#    #+#             */
/*   Updated: 2023/07/31 01:33:52 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*protects(char *get_line)
{
	size_t	i;
	char	*hold;

	i = 0;
	while (get_line[i] != '\0' && get_line[i] != '\n')
		i++;
	if (get_line[i] == '\0')
		return (NULL);
	hold = ft_substr(get_line, i + 1, ft_strlen(get_line) - i);
	if (*hold == '\0')
	{
		free(hold);
		hold = NULL;
	}
	get_line[i + 1] = '\0';
	return (hold);
}

char	*read_line(int fd, char *buffer, char *hold)
{
	int		readline;
	char	*temp;

	readline = 1;
	while (readline != '\0')
	{
		readline = read(fd, buffer, BUFFER_SIZE);
		if (readline == -1)
			return (0);
		else if (readline == 0)
			break ;
		buffer[readline] = '\0';
		if (!hold)
			hold = ft_strdup("");
		temp = hold;
		hold = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (hold);
}

char	*get_next_line(int fd)
{
	char			*get_line;
	static char		*hold;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	get_line = read_line(fd, buffer, hold);
	free(buffer);
	buffer = NULL;
	if (!get_line)
	{
		free(hold);
		hold = NULL;
		return (NULL);
	}
	hold = protects(get_line);
	return (get_line);
}

char	*line2(int *fd, char *line)
{
	write(fd[1], line, ft_strlen(line));
	free(line);
	line = get_next_line(0);
	return (line);
}

void	aux2(int *fd, char *line, char *limiter)
{
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd[1]);
			exit(0);
		}
		line = line2(fd, line);
	}
	close(fd[1]);
	exit(1);
}
