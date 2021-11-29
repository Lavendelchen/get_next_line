/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:44:50 by shaas             #+#    #+#             */
/*   Updated: 2021/09/22 13:44:23 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*split_remainder_1(char **line,
	char **remainder, char **buffer, int newline)
{
	*line = ft_substr(*remainder, 0, (newline + 1));
	if (!(*line))
		return (ft_free_helper(line, remainder, NULL));
	*buffer = ft_substr(*remainder, (newline + 1), BUFFER_SIZE);
	if (!(*buffer))
		return (ft_free_helper(line, remainder, NULL));
	free (*remainder);
	*remainder = ft_substr(*buffer, 0, BUFFER_SIZE);
	if (!(*remainder))
		return (ft_free_helper(line, remainder, buffer));
	free (*buffer);
	return (*line);
}

static char	*split_remainder_2(char **line,
	char **remainder, char **buffer, int newline)
{
	*remainder = ft_substr(*buffer, 0, (newline + 1));
	if (!(*remainder))
		return (ft_free_helper(remainder, buffer, line));
	*line = ft_linejoin(*line, *remainder);
	if (!(*line))
		return (ft_free_helper(buffer, NULL, NULL));
	free (*remainder);
	*remainder = ft_substr(*buffer, (newline + 1), BUFFER_SIZE);
	if (!(*remainder))
		return (ft_free_helper(remainder, buffer, line));
	free (*buffer);
	return (*line);
}

static char	*reader(int fd, char **remainder, char **buffer, char **line)
{
	int	bytes_read;
	int	newline;

	while (1)
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free_helper(remainder, buffer, line));
		if (bytes_read == 0)
		{
			ft_free_helper(buffer, NULL, NULL);
			if (ft_strlen(*line) != 0)
				return (*line);
			return (ft_free_helper(line, NULL, NULL));
		}
		(*buffer)[bytes_read] = '\0';
		newline = ft_find_newline(*buffer);
		if (newline != -1)
			return (split_remainder_2(line, remainder, buffer, newline));
		*line = ft_linejoin(*line, *buffer);
		if (!(*line))
			return (ft_free_helper(buffer, NULL, NULL));
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;
	int			newline;

	newline = ft_find_newline(remainder);
	if (newline != -1)
		return (split_remainder_1(&line, &remainder, &buffer, newline));
	buffer = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	line = (char *)malloc(sizeof(char) * 1);
	if (!buffer || !line || fd < 0)
		return (ft_free_helper(&remainder, &buffer, &line));
	line[0] = '\0';
	line = ft_linejoin(line, remainder);
	if (!line)
		return (ft_free_helper(&buffer, NULL, NULL));
	ft_free_helper(&remainder, NULL, NULL);
	return (reader(fd, &remainder, &buffer, &line));
}
