#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

char *get_next_line(int fd)
{
	char	*buffer;
	t_list	*line_list;
	int		bytes_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE); // whyd you do that kamis. why no space for null
	line_list = ft_lstnew(NULL);
	while ()
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		
	}
	return (buffer);
}

int main()
{
	int		fd_1;
	int		fd_2;
	char	*line;

	fd_1 = open("test.txt", O_RDONLY);
	fd_2 = open("get_next_line.c", O_RDONLY);
	line = malloc(sizeof(char) * BUFFER_SIZE);
	while ((line = get_next_line(fd_1)) != NULL)
		printf("[%s]\n", line);
	printf("[%s]", line);
	free (line);
}
