/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:04:58 by momazouz          #+#    #+#             */
/*   Updated: 2024/02/07 00:05:27 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}



char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == NULL)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (s2 == NULL || s1 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_cpyline(char *line, int i)
{
	char	*str;

	while (line[i] != '\0' && line[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	str[i] = '\n';
	i = -1;
	while (line[++i] != '\0' && line[i] != '\n')
		str[i] = line[i];
	if (str[i] == '\n')
		i++;
	str[i] = '\0';
	return (str);
}

char	*ft_newline(char *oldline)
{
	size_t	j;
	size_t	i;
	char	*str;

	i = 0;
	while (oldline[i] != '\0' && oldline[i] != '\n')
		i++;
	if (oldline[i] == '\0')
	{
		free(oldline);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(oldline) - i + 1);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (oldline[i])
		str[j++] = oldline[i++];
	str[j] = '\0';
	free(oldline);
	return (str);
}
