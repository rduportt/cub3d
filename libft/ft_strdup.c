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

char	*ft_strdup(const char *source)
{
	char	*tab;
	int		i;

	i = 0;
	while (source[i])
		i++;
	tab = malloc((i + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (source[i])
	{
		tab[i] = source[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
