/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:03:38 by momazouz          #+#    #+#             */
/*   Updated: 2024/02/07 00:04:03 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_readfile(int fd, char *cpy)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytes = 1;
	while (ft_strchr(cpy, '\n') == NULL && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(cpy);
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		cpy = ft_strjoin(cpy, buffer);
	}
	free(buffer);
	return (cpy);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	str = ft_readfile(fd, str);
	if (str == NULL)
		return (NULL);
	if (!str[0])
		return (free(str), str = NULL, NULL);
	line = ft_cpyline(str, 0);
	str = ft_newline(str);
	return (line);
}