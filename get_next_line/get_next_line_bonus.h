/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <tirimesc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:21:25 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/25 13:21:28 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_strlen_gnl(char const *s);
char	*last_line(char *line);
char	*new_buffer(char **line);
char	*ft_strchr_gnl(const char *string, int searchedChar);
void	*ft_memmove_gnl(void *destination, const void *source, size_t size);
char	*ft_strdup_gnl(char *source);
void	free_buffer(char **buffer);
#endif