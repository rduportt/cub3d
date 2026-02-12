/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:44:24 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/12 17:03:29 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t		i;
	const char	*memo;

	i = 0;
	memo = (const char *)memoryBlock;
	while (i < size)
	{
		if (memo[i] == (const char)searchedChar)
			return ((void *)&memo[i]);
		i++;
	}
	return (NULL);
}
