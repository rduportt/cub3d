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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*tab;

	s_len = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		tab = malloc ((s_len - start + 1) * sizeof(char));
	else
		tab = malloc ((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (i < len && s[start + i])
	{
		tab[i] = s[start + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

/*  int	main(void)
{
	char	tab[] = "hola";
	char	*test;
	int	i = 0;
	int	start = 5;
	size_t	len = 2;

	test = ft_substr(tab, start, len);
	while (i < len)
		printf("%c", test[i++]);
}  */