/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <tirimesc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:21:25 by tirimesc          #+#    #+#             */
/*   Updated: 2024/12/19 17:22:26 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_strchr_gnl(const char *string, int searchedChar)
{
	int				i;
	unsigned char	c;

	c = (unsigned char)searchedChar;
	i = 0;
	while (string[i])
	{
		if ((unsigned char)string[i] == c)
			return ((char *)&string[i]);
		i++;
	}
	if ((unsigned char)string[i] == c)
		return ((char *)&string[i]);
	return (NULL);
}

char	*extra_get_next_line(int bytes, char *read_line,
	char **buffer)
{
	char	*result;

	free(read_line);
	if (bytes <= 0 && (!*buffer || !**buffer))
	{
		free_buffer(buffer);
		return (NULL);
	}
	result = last_line(*buffer);
	*buffer = new_buffer(buffer);
	if (!*buffer || !**buffer)
		free_buffer(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*buffer[1024];
	char			*read_line;
	int				bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	read_line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_line)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, read_line, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(read_line);
			return (NULL);
		}
		read_line[bytes] = '\0';
		buffer[fd] = ft_strjoin_gnl(buffer[fd], read_line);
		if (ft_strchr_gnl(buffer[fd], '\n'))
			break ;
	}
	return (extra_get_next_line(bytes, read_line, &buffer[fd]));
}

void	free_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}
/* int	main(void)
{
	int		fd;
	char	*d;
	int		i ;

	i = 0;
	fd = open("file.txt", O_RDONLY);
	while (i < 4)
	{
		d = get_next_line(fd);
		printf("%s", d);
		free(d);
		i++;
	}
	close(fd);
}
 */