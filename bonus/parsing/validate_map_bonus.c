/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:03:10 by medo              #+#    #+#             */
/*   Updated: 2025/02/04 14:43:12 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	check_invalid_char(t_base *game, char c)
{
	if (c != '1' && c != ' ' && c != '0' && c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != 'D')
	{
		ft_printf_err("Error\nInvalid character in map\n");
		free_split(game->map);
		free_texture(game->textures);
		free_path(game);
		exit(1);
	}
}

void	handle_player(t_base *game, int i, int j, int *player_found)
{
	if (*player_found)
	{
		ft_printf_err("Error\nMultiple player positions found\n");
		free_split(game->map);
		free_texture(game->textures);
		free_path(game);
		exit(1);
	}
	*player_found = 1;
	game->player_x = j;
	game->player_y = i;
}

void	check_map_closed(t_base *game, char c, int i, int j)
{
	int	vertical_wall;
	int	horizontal_wall;

	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')
	{
		if (i == 0 || j == 0 || i == game->map_height - 1
			|| j == game->map_width - 1 || game->map[i - 1][j] == ' '
			|| game->map[i + 1][j] == ' ' || game->map[i][j - 1] == ' '
			|| game->map[i][j + 1] == ' ')
		{
			error_map_close(game);
		}
		else if (c == 'D')
		{
			vertical_wall = (game->map[i - 1][j] == '1') + (game->map[i
					+ 1][j] == '1');
			horizontal_wall = (game->map[i][j - 1] == '1') + (game->map[i][j
					+ 1] == '1');
			if (vertical_wall < 2 && horizontal_wall < 2)
			{
				error_of_door(game);
			}
		}
	}
}

void	validate_player_presence(t_base *game, int player_found)
{
	if (!player_found)
	{
		ft_printf_err("Error\nNo player position found\n");
		free_split(game->map);
		free_texture(game->textures);
		free_path(game);
		exit(1);
	}
}

void	validate_map(t_base *game)
{
	int		i;
	int		j;
	int		player_found;
	char	c;

	i = 0;
	player_found = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			c = game->map[i][j];
			check_invalid_char(game, c);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				handle_player(game, i, j, &player_found);
				game->player_dir = c;
			}
			check_map_closed(game, c, i, j);
			j++;
		}
		i++;
	}
	validate_player_presence(game, player_found);
}
