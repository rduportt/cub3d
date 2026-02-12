/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:38:52 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/12 16:08:42 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

void	*ft_memset(void *dest, int c, size_t count);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *source, size_t size);
void	*ft_memmove(void *destination, const void *source, size_t size);
void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
int		ft_atoi(const char *String);
int		ft_isalnum(int character);
int		ft_isalpha(int character);
int		ft_isdigit(int character);
int		ft_isascii(int character);
char	*ft_strchr(const char *string, int searchedChar);
int		ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strlen(const char *String);
char	*ft_strnstr(const char *s1, const char *s2, size_t size);
int		ft_tolower(int character);
int		ft_toupper(int character);
void	*ft_calloc(size_t elementCount, size_t elementSize);
char	*ft_strdup(const char *source);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strrchr(const char *String, int searchedChar);
int		ft_isprint(int character);
char	*ft_strnstr(const char *s1, const char *s2, size_t size);
int		ft_strncmp(const char *first, const char *second, size_t lenght);

#endif // LIBFT_H
