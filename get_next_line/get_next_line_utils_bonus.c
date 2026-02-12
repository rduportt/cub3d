/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <tirimesc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:21:25 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/25 13:21:28 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*tab;
	int		len;

	i = 0;
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	tab = malloc ((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			tab[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
		tab[i++] = s2[j++];
	tab[i] = '\0';
	free (s1);
	return (tab);
}

int	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*last_line(char *line)
{
	int		i;
	char	*result;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	result = malloc((i + 2) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memmove_gnl(result, line, i);
	result[i] = '\0';
	return (result);
}

char	*new_buffer(char **line)
{
	int		i;
	char	*newbuffer;

	i = 0;
	if (!line || !*line)
		return (NULL);
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\n')
		i++;
	if ((*line)[i] == '\0')
	{
		free_buffer(line);
		return (NULL);
	}
	newbuffer = malloc ((ft_strlen_gnl(*line) - i + 1) * sizeof(char));
	if (!newbuffer)
		return (NULL);
	ft_memmove_gnl(newbuffer, (*line + i), ft_strlen_gnl(*line) - i + 1);
	free(*line);
	*line = NULL;
	return (newbuffer);
}

void	*ft_memmove_gnl(void *destination, const void *source, size_t size)
{
	size_t		i;
	char		*dest;
	const char	*src;

	i = 0;
	dest = (char *) destination;
	src = (const char *) source;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src < dest)
	{
		while (size-- > 0)
			dest[size] = src[size];
	}
	else
	{
		while (i < size)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}
