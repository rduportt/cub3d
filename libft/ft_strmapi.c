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

/* char	sample_function(unsigned int i, char c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	else if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*tab;
	int					len;

	len = ft_strlen(s);
	i = 0;
	tab = malloc ((len + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	while (s[i])
	{
		tab[i] = f(i, s[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

/*  int	main()
{
	char	*strmapi;

	strmapi = ft_strmapi("LoReM iPsUm", sample_function);
	printf("%s\n", strmapi);
}  */