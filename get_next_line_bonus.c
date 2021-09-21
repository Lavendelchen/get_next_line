/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:44:50 by shaas             #+#    #+#             */
/*   Updated: 2021/09/21 18:11:53 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char	*ft_free_helper(char **str1, char **str2, char **str3)
{
	if (str1)
	{
		free (*str1);
		*str1 = NULL;
	}
	if (str2)
	{
		free (*str2);
		*str2 = NULL;
	}
	if (str3)
	{
		free (*str3);
		*str3 = NULL;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	num;

	num = 0;
	while (*s != '\0')
	{
		num++;
		s++;
	}
	return (num);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && s[i + start] != '\0' && start < ft_strlen(s))
		i++;
	subs = (char *)malloc(sizeof(char) * (i + 1)); // every substring is allocated. need to free when used!!
	if (!subs)
		return (NULL);
	while (j < i)
	{
		subs[j] = s[j + start];
		j++;
	}
	subs[j] = '\0';
	return (subs);
}

char	*ft_linejoin(char *old_line, char *add)
{
	int		i;
	int		j;
	size_t	len_1;
	size_t	len_2;
	char	*new_line;

	if (!add)
		return (old_line);
	i = 0;
	j = 0;
	len_1 = ft_strlen(old_line);
	len_2 = ft_strlen(add);
	new_line = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!new_line)
		return (ft_free_helper(&old_line, &add, NULL));
	while (old_line[j] != '\0')
		new_line[i++] = old_line[j++];
	while (*add != '\0')
		new_line[i++] = *(add++);
	new_line[i] = '\0';
	free (old_line);
	return (new_line);
}

int	ft_find_newline(char *buffer)
{
	int	i;

	i = 0;
	if (buffer == NULL)
		return (-1);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_split_remainder_1(char **line, char **remainder, char **buffer, int newline)
{
	*line = ft_substr(*remainder, 0, (newline + 1));
	if (!(*line))
		return (ft_free_helper(line, remainder, NULL));
	*buffer = ft_substr(*remainder, (newline + 1), BUFFER_SIZE); // literally a buffer for the rest of the string
	if (!(*buffer))
		return (ft_free_helper(line, remainder, NULL));
	free (*remainder);
	*remainder = ft_substr(*buffer, 0, BUFFER_SIZE);
	if (!(*remainder))
		return (ft_free_helper(line, remainder, buffer));
	free (*buffer);
	return (*line);
}

char	*ft_split_remainder_2(char **line, char **remainder, char **buffer, int newline)
{
	*remainder = ft_substr(*buffer, 0, (newline + 1)); // this is what is to be added. remainder[fd] is used as a spare pointer, it's not actually the remainder[fd] in this case. rather the exact opposite, the end of the line.// not sure if newline + 1 is correct size -> checked, it is.
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

char	*ft_read(int fd, char **remainder, char **buffer, char **line)
{
	int	bytes_read;
	int	newline;

	while (1)
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read < 0) // read fail
			return (ft_free_helper(remainder, buffer, line));
		if (bytes_read == 0) // it's the case when we're at EOF
		{
			ft_free_helper(buffer, NULL, NULL);
			if (ft_strlen(*line) != 0) // case where there was still a remainder[fd]
				return (*line);
			return (ft_free_helper(line, NULL, NULL));
		}
		(*buffer)[bytes_read] = '\0';
		newline = ft_find_newline(*buffer);
		if (newline != -1) // case when we're at end of line
			return (ft_split_remainder_2(line, remainder, buffer, newline));
		*line = ft_linejoin(*line, *buffer);
		if (!(*line))
			return (ft_free_helper(buffer, NULL, NULL));
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder[OPEN_MAX];
	char		*buffer;
	char		*line;
	int			newline;

	newline = ft_find_newline(remainder[fd]);
	if (newline != -1) // this is for the case that the entire line is contained in the remainder[fd]
		return (ft_split_remainder_1(&line, &remainder[fd], &buffer, newline));
	buffer = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	line = (char *)malloc(sizeof(char) * 1);
	if (!buffer || !line || fd < 0)
		return (ft_free_helper(&remainder[fd], &buffer, &line));
	line[0] = '\0';
	line = ft_linejoin(line, remainder[fd]);
	if (!line)
		return (ft_free_helper(&buffer, NULL, NULL));
	ft_free_helper(&remainder[fd], NULL, NULL);
	return (ft_read(fd, &remainder[fd], &buffer, &line));
}

//int	main(void)
//{
//	int		fd_1;
//	int		fd_2;
//	char	*line;
//
//	fd_1 = open("test.txt", O_RDONLY);
//	fd_2 = open("get_next_line.c", O_RDONLY);
//	while ((line = get_next_line(fd_1)) != NULL)
//	{
//		printf("[%s]\n", line);
//		free (line);
//		//printf("here\n"); //testing
//	}
//	printf("[%s]", line);
//	close(fd_1);
//	close(fd_2);
//	free(line);
//}
