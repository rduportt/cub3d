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

char	*wstrdup(const char *source, int i, int start)
{
	char	*tab;
	int		index;

	index = 0;
	tab = malloc(((i - start) + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	while (start < i)
	{
		tab[index] = source[start];
		index++;
		start++;
	}
	tab[index] = '\0';
	return (tab);
}

char	**count(char const *s, char c)
{
	int		i;
	char	**tab;
	int		start;
	int		words;

		i = 0;
	start = -1;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && start == -1)
			start = i;
		else if (s[i] == c && start != -1)
		{
			words++;
			start = -1;
		}
		i++;
	}
	if (start != -1)
		words++;
	tab = malloc ((words + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	return (tab);
}

void	free_tab(char **tab, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**exec_split(int words, char **tab, const char *s, char c)
{
	int	i;
	int	start;

	i = 0;
	start = -1;
	while (s[i])
	{
		if (s[i] != c && start == -1)
			start = i;
		else if (s[i] == c && start != -1)
		{
			tab[words++] = wstrdup(s, i, start);
			if (!tab[words - 1])
			{
				free_tab(tab, words);
				return (NULL);
			}
			start = -1;
		}
		i++;
	}
	if (start != -1)
		tab[words++] = wstrdup(s, i, start);
	tab[words] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;

	words = 0;
	if (!s)
		return (NULL);
	tab = count(s, c);
	if (!tab)
		return (NULL);
	tab = exec_split(words, tab, s, c);
	return (tab);
}
