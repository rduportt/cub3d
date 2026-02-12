/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:21:55 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/11 18:47:27 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;	

	i = 0;
	dest_len = 0;
	src_len = 0;
	while (src[src_len])
		src_len++;
	while (dst[dest_len] && dest_len < size)
		dest_len++;
	if (size <= dest_len)
		return (src_len + size);
	while (src[i] && (dest_len + i) < size - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if ((dest_len + i) < size)
		dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
