#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_next_line(int fd)
{
	char *buff;
	int fd_read;

	buff = malloc(sizeof(char) * BUFFER_SIZE);
	fd_read = read(fd, buff, BUFFER_SIZE);
	if (fd_read == 0 || fd_read < 0)
		return NULL;
	return buff;
}

int main()
{
	int		fd_1;
	int		fd_2;
	char	*line;

	fd_1 = open("test.txt", O_RDONLY);
	fd_2 = open("get_next_line.c", O_RDONLY);
	// line = get_next_line(fd_1);
	while ((line = get_next_line(fd_1)))
		printf("line = %s\n", line);6
}
