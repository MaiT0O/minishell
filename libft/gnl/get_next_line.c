/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:50:45 by ebansse           #+#    #+#             */
/*   Updated: 2024/12/09 15:47:04 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*join_and_free(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

static char	*extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*extract_next_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	line = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	j = 0;
	while (str[i])
		line[j++] = str[i++];
	free(str);
	return (line);
}

static char	*read_line(int fd, char *content)
{
	char	*buffer;
	ssize_t	bytes_reads;

	if (!content)
		content = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_reads = 1;
	while (bytes_reads > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_reads = read(fd, buffer, BUFFER_SIZE);
		if (bytes_reads == -1)
		{
			free(buffer);
			free(content);
			return (NULL);
		}
		buffer[bytes_reads] = '\0';
		content = join_and_free(content, buffer);
	}
	free(buffer);
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = extract_next_line(buffer);
	return (line);
}

/*#include <stdio.h>

int main(void)
{
	int	fd;
	int	i;
	static char *str;

	fd = open("./test.txt", O_RDONLY);
	i = 0;
	while (i < 3)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	return (0);
}*/