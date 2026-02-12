/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:24:36 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/12 16:06:57 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t size)
{
	size_t		i;
	char		*destination;
	const char	*src;

	i = 0;
	destination = (char *) dest;
	src = (const char *) source;
	if (source == NULL && dest == NULL)
		return (NULL);
	while (i < size)
	{	
		destination[i] = src[i];
		i++;
	}
	return (destination);
}
