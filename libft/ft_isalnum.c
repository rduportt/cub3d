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

int	ft_isalnum(int character)
{
	if ((character >= 48 && character <= 57)
		|| (character >= 65 && character <= 90)
		|| (character >= 97 && character <= 122))
		return (1);
	return (0);
}
