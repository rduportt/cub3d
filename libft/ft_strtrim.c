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

int	is_sett(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		j;
	char	*tab;

	i = 0;
	len = ft_strlen(s1);
	j = 0;
	while (is_sett(s1[i], set) == 1)
		i++;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	while (is_sett(s1[len - 1], set) == 1)
		len--;
	tab = malloc(((len - i) + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	while (i < len)
	{
		tab[j] = s1[i];
		i++;
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
