#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char	*ft_linejoin(char *old_line, const char *add)
{
	int		i;
	size_t	len_1;
	size_t	len_2;
	char	*new_line;

	i = 0;
	len_1 = ft_strlen(old_line);
	len_2 = ft_strlen(add);
	new_line = (char *)malloc(len_1 + len_2 + 1);
	if (new_line == NULL)
		return (new_line);
	while (*old_line != '\0')
	{
		new_line[i] = *old_line;
		i++;
		old_line++;
	}
	while (*add != '\0')
	{
		new_line[i] = *add;
		i++;
		add++;
	}
	new_line[i] = '\0';
	free (old_line);
	return (new_line);
}

int	ft_find_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remainder;
	int			bytes_read;
	int			newline;

	if (fd < 0)
		return (NULL);
	buffer = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (buffer == NULL)
		return (NULL);
	line = (char *)malloc(sizeof(char) * 1);
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	while (TRUE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0) // it's the case when we're at EOF
			break ; // i think that's actually all we have to do?
		buffer[bytes_read] = '\0';
		newline = ft_find_newline(buffer);
		if (newline != -1) // case when we're at end of line
		{
			remainder = //dynamic??
			break ; // that's also not it
		}
		line = ft_linejoin(line, buffer);
	}
	free (buffer);
	return (line);
}

int	main()
{
	int		fd_1;
	int		fd_2;
	char	*line;

	fd_1 = open("test.txt", O_RDONLY);
	fd_2 = open("get_next_line.c", O_RDONLY);
	while ((line = get_next_line(fd_1)) != NULL)
	{
		printf("[%s]\n", line);
		free (line);
	}
	printf("[%s]", line);
	close(fd_1);
	close(fd_2);
	free(line);
}
