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

char	*ft_strchr(const char *string, int searchedChar)
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
