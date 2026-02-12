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

char	*ft_strrchr(const char *String, int searchedChar)
{
	int				i;
	char			*tab;
	unsigned char	c;

	c = (unsigned char)searchedChar;
	i = 0;
	tab = NULL;
	while (String[i])
	{
		if (String[i] == c)
			tab = (char *)&String[i];
		i++;
	}
	if (String[i] == c)
		tab = (char *)&String[i];
	return (tab);
}
