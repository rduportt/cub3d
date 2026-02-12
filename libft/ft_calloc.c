/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:54:48 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/13 13:54:50 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char		*tab;
	size_t		i;

	i = 0;
	tab = malloc(elementCount * elementSize);
	if (tab == NULL)
		return (NULL);
	while (tab[i])
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}
