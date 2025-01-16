/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:14:52 by medo              #+#    #+#             */
/*   Updated: 2025/01/07 17:27:59 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_printf_err(char *str)
{
	size_t	i;

	i = ft_strlen2(str);
	write(2, str, i);
}

char	*add_apaces_row(char *row, size_t len, size_t map_width)
{
	char	*new_row;
	size_t	j;

	new_row = malloc(map_width + 1);
	j = 0;
	while (j < map_width)
	{
		if (j < len)
			new_row[j] = row[j];
		else
			new_row[j] = ' ';
		j++;
	}
	new_row[map_width] = '\0';
	return (new_row);
}

void	pad_map(t_base *game)
{
	int		i;
	int		j;
	size_t	len;
	char	*new_row;

	i = 0;
	while (i < game->map_height)
	{
		len = ft_strlen2(game->map[i]);
		if (len < game->map_width)
		{
			new_row = add_apaces_row(game->map[i], len, game->map_width);
			free(game->map[i]);
			game->map[i] = new_row;
		}
		i++;
	}
}

int	check_path(char *name)
{
	size_t	i;
	int		j;
	int		r;

	i = ft_strlen2(name);
	j = 4;
	r = 0;
	while (j > 0 && i > 0)
	{
		if (name[i - 1] == ".cub"[j - 1])
		{
			r++;
			j--;
			i--;
		}
		else
			break ;
	}
	if (!(r == 4 && j == 0))
	{
		ft_printf_err("Error\n the file name of map doesn't valide\n");
		return (1);
	}
	return (0);
}

void	parsing(t_base *game, char *file_name)
{
	int	fd;

	if (check_path(file_name) == 1)
		exit(1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_err("Error\n the file doesn't exist\n");
		exit(1);
	}
	parse_map(game, fd);
}
