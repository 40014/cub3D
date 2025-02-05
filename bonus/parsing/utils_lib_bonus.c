/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:10:50 by medo              #+#    #+#             */
/*   Updated: 2025/02/04 14:42:56 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	ft_isdigit_str(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	r;

	i = 0;
	n = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	return (r * n);
}

char	*ft_strchr1(const char *s, int i)
{
	unsigned char	ch;

	ch = i;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == i)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*trim;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (s1 != NULL && set != NULL && *s1 != '\0')
	{
		i = 0;
		j = ft_strlen2(s1);
		while (s1[i] && ft_strchr1(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr1(set, s1[j - 1]) && j > i)
			j--;
		trim = (char *)malloc(sizeof(char) * (j - i + 1));
		if (trim)
			ft_strlcpy(trim, &s1[i], (j - i) + 1);
	}
	else
	{
		trim = (char *)malloc(1);
		if (trim)
			*trim = '\0';
	}
	return (trim);
}
