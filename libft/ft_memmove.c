/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:53:59 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/12 14:46:06 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
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
