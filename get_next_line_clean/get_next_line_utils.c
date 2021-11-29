/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:20:37 by shaas             #+#    #+#             */
/*   Updated: 2021/09/22 13:37:52 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	subs = (char *)malloc(sizeof(char) * (i + 1));
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
