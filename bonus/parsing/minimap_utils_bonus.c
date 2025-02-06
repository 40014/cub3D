/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:43:46 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 18:06:08 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	ft_draw_square(t_base *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale_size;

	scale_size = CUB_SIZE / MINI_MAP_SIZE;
	j = 0;
	while (j < scale_size)
	{
		i = 0;
		while (i < scale_size)
		{
			my_mlx_pixel_put(game, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

int	get_color(t_base *game, int j, int i)
{
	int	color;

	color = 0x009900FF;
	if (game->player_infos->map2[j][i] == '1')
		color = 0x000000;
	else if (game->player_infos->map2[j][i] == '0')
		color = 0xAAAAAA;
	else if (game->player_infos->map2[j][i] == 'D')
		color = 0xff8633;
	else if (game->player_infos->map2[j][i] == 'N'
			|| game->player_infos->map2[j][i] == 'S'
			|| game->player_infos->map2[j][i] == 'W'
			|| game->player_infos->map2[j][i] == 'E')
		color = 0xAAAAAA;
	return (color);
}

void	draw_circle(t_base *game, double center_x, double center_y, int radius)
{
	int	x;
	int	y;
	int	radius_squared;
	int	color;

	radius_squared = radius * radius;
	y = -radius;
	color = 0xFF0000;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius_squared)
				my_mlx_pixel_put(game, center_x + x, center_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_direction(t_base *game, t_mini_range *mini_map_range,
		double line_lenght, int color)
{
	double	x1;
	double	y1;
	int		x;
	int		y;
	int		scaled_tile_size;

	scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
	while (line_lenght >= 0)
	{
		x1 = mini_map_range->minimap_p_x - (mini_map_range->start_i
				* scaled_tile_size) + cos(game->player_infos->rotation_angle)
			* line_lenght;
		y1 = mini_map_range->minimap_p_y - (mini_map_range->start_y
				* scaled_tile_size) + sin(game->player_infos->rotation_angle)
			* line_lenght;
		my_mlx_pixel_put(game, x1, y1, color);
		line_lenght--;
	}
}
