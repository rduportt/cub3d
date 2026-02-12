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

void	numm(int n, long long value, int num, char *tab)
{
	int	i;

	i = 0;
	if (n < 0)
		value = -value;
	tab[num] = '\0';
	if (value == 0)
		tab[0] = '0';
	while (value > 0)
	{
		num--;
		tab[num] = (value % 10) + '0';
		value = value / 10;
		i++;
	}
	if (n < 0)
		tab[0] = '-';
}

char	*ft_itoa(int n)
{
	long long	value;
	int			num;
	char		*tab;

	num = 0;
	value = n;
	if (n <= 0)
	{
		num++;
		value = -value;
	}
	while (value > 0)
	{
		num++;
		value = value / 10;
	}
	value = n;
	tab = malloc ((num + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	numm(n, value, num, tab);
	return (tab);
}
