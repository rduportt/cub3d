/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:11:53 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/13 13:11:55 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nb)
{
	int	i;
	int	result;
	int	signe;

	i = 0;
	result = 0;
	signe = 1;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '-')
	{
		signe = -1;
		i++;
	}
	else if (nb[i] == '+')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
		result = result * 10 + (nb[i++] - '0');
	return (result * signe);
}
