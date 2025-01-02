/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:49:15 by hdrahm            #+#    #+#             */
/*   Updated: 2024/01/27 02:46:26 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin(char const *s1, char const *s2);

void	*ft_calloc(size_t count, size_t size);

void	*ft_calloc(size_t count, size_t size);

void	ft_bzero(void *s, size_t n);

int		ft_strchr(const char *s, int c);

char	*get_rest(char *line, int j);

char	*ft_seperate_rest(char *line, int c, int i, int j);

char	*fill(char *str, int c);

char	*ft_fill_buf(int fd, char *str, ssize_t b);

char	*get_next_line(int fd);

#endif
