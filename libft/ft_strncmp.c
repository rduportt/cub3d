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

int	ft_strncmp(const char *first, const char *second, size_t lenght)
{
	size_t	i;

	i = 0;
	while (i < lenght && (first[i] || second[i]))
	{
		if ((unsigned const char)first[i] != (unsigned const char)second[i])
			return ((unsigned const char)first[i]
				- (unsigned const char)second[i]);
		i++;
	}
	return (0);
}
