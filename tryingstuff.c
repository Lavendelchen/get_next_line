#include <stdlib.h>
#include <stdio.h>

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
	subs = (char *)malloc(i + 1); // every substring is allocated. need to free when used!!
	if (subs == NULL)
		return (subs);
	while (j < i)
	{
		subs[j] = s[j + start];
		j++;
	}
	subs[j] = '\0';
	return (subs);
}

int	ft_find_newline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	main()
{
	static char	*hi;
	int			newline;

	newline = ft_find_newline("\nabcde is a stupid name");
	hi = ft_substr("\nabcde is a stupid name", (newline + 1), 21);
	printf("newline: %d, string = [%s]", newline, hi);
	free (hi);
	hi = NULL; // if i leave this out, malloc error. you can't free a pointer twice.
	free (hi);
}
