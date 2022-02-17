#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	if (str == NULL)
		return (0);
	int i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

int	ft_strchr(char *str, int c)
{
	if (str == NULL)
		return (-1);
	int i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char *ft_strdup_len(char *str, int len)
{
	if (str == NULL)
		return (NULL);
	char *dup = malloc(len + 1);
	int i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char *ft_strjoin(char *str1, char *str2)
{
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	int i = 0;
	int j = 0;

	char *join = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	while (str1 != NULL && str1[i] != 0)
	{
		join[j] = str1[i];
		i++;
		j++;
	}
	i = 0;
	while (str2 != NULL && str2[i] != 0)
	{
		join[j] = str2[i];
		i++;
		j++;
	}
	join[j] = '\0';
	return (join);
}

char	*full_line_in_buffer(char **buffer)
{
	char *ret;
	char *bufbuf;
	int n = ft_strchr(*buffer, '\n');
	ret = ft_strdup_len(*buffer, n + 1);
	bufbuf = ft_strdup_len(&((*buffer)[n + 1]), ft_strlen(&((*buffer)[n + 1])));
	free (*buffer);
	*buffer = bufbuf;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			b_r;
	char		*ret;

	if (ft_strchr(buffer, '\n') != -1)
		return (full_line_in_buffer(&buffer));
	char *reading = malloc(BUFFER_SIZE + 1);
	reading[BUFFER_SIZE] = 0;
	char *bufbuf;
	while (ft_strchr(buffer, '\n') == -1)
	{
		b_r = read(fd, reading, BUFFER_SIZE);
		if (b_r == 0)
		{
			free (reading);
			ret = ft_strdup_len(buffer, ft_strlen(buffer));
			free (buffer);
			buffer = NULL;
			return (ret);
		}
		bufbuf = ft_strjoin(buffer, reading);
		free (buffer);
		buffer = bufbuf;
	}
	int n = ft_strchr(buffer, '\n');
	ret = ft_strdup_len(buffer, n + 1);
	bufbuf = ft_strdup_len(&buffer[n + 1], ft_strlen(&buffer[n + 1]));
	free (buffer);
	buffer = bufbuf;
	free (reading);
	return (ret);
}

int	main(void)
{
	//int		fd_1;
	int		fd_2;
	char	*line;

	//fd_1 = open("test.txt", O_RDONLY);
	fd_2 = open("get_next_line.c", O_RDONLY);
	while ((line = get_next_line(fd_2)) != NULL)
	{
		printf("%s", line);
		free (line);
		//printf("here\n"); //testing
	}
	printf("%s", line);
	//close(fd_1);
	close(fd_2);
	free(line);
}
