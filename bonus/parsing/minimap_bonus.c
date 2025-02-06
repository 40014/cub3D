/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:43:46 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 18:05:26 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_minimap_walls(t_base *game, t_mini_range *mini_map_range)
{
	int	i;
	int	j;
	int	scaled_tile_size;
	int	x;
	int	y;

	scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
	j = mini_map_range->start_y;
	while (j <= mini_map_range->end_y && j < game->map_height)
	{
		i = mini_map_range->start_i;
		while (i <= mini_map_range->end_i && i < game->map_width)
		{
			x = (i - mini_map_range->start_i) * scaled_tile_size;
			y = (j - mini_map_range->start_y) * scaled_tile_size;
			ft_draw_square(game, x, y, get_color(game, j, i));
			i++;
		}
		j++;
	}
}

void	fix_start_end_i(t_mini_range *mini_map_range, t_base *game)
{
	if (mini_map_range->start_i < 0 && mini_map_range->end_i > game->map_width)
	{
		while (mini_map_range->start_i < 0)
			mini_map_range->start_i++;
		while (mini_map_range->end_i > game->map_width)
			mini_map_range->end_i--;
	}
	else if (mini_map_range->start_i < 0)
	{
		while (mini_map_range->start_i < 0)
		{
			mini_map_range->start_i++;
			if (mini_map_range->end_i < game->map_width)
				mini_map_range->end_i++;
		}
	}
	else if (mini_map_range->end_i > game->map_width)
	{
		while (mini_map_range->end_i > game->map_width)
		{
			mini_map_range->end_i--;
			if (mini_map_range->start_i > 0)
				mini_map_range->start_i--;
		}
	}
}

void	fix_start_end_y(t_mini_range *mini_map_range, t_base *game)
{
	if (mini_map_range->start_y < 0 && mini_map_range->end_y > game->map_height)
	{
		while (mini_map_range->start_y < 0)
			mini_map_range->start_y++;
		while (mini_map_range->end_y > game->map_height)
			mini_map_range->end_y--;
	}
	else if (mini_map_range->start_y < 0)
	{
		while (mini_map_range->start_y < 0)
		{
			mini_map_range->start_y++;
			if (mini_map_range->end_y < game->map_height)
				mini_map_range->end_y++;
		}
	}
	else if (mini_map_range->end_y > game->map_height)
	{
		while (mini_map_range->end_y > game->map_height)
		{
			mini_map_range->end_y--;
			if (mini_map_range->start_y > 0)
				mini_map_range->start_y--;
		}
	}
}

void	find_mini_map_range(t_mini_range *mini_map_range, t_base *game)
{
	int	scaled_tile_size;
	int	i;
	int	y;

	scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
	mini_map_range->minimap_p_x = game->player_infos->i / MINI_MAP_SIZE;
	mini_map_range->minimap_p_y = game->player_infos->j / MINI_MAP_SIZE;
	i = (int)mini_map_range->minimap_p_x / scaled_tile_size;
	y = (int)mini_map_range->minimap_p_y / scaled_tile_size;
	mini_map_range->start_i = i - CELLS_RANGE;
	mini_map_range->end_i = i + CELLS_RANGE;
	mini_map_range->start_y = y - CELLS_RANGE;
	mini_map_range->end_y = y + CELLS_RANGE;
	fix_start_end_i(mini_map_range, game);
	fix_start_end_y(mini_map_range, game);
}

void	draw_minimap(t_base *game)
{
	t_mini_range	mini_map_range;
	int				scaled_tile_size;
	double			saved_j;
	double			saved_i;
	int				saved_cub_size;

	scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
	find_mini_map_range(&mini_map_range, game);
	draw_minimap_walls(game, &mini_map_range);
	draw_circle(game, mini_map_range.minimap_p_x - (mini_map_range.start_i
			* scaled_tile_size), mini_map_range.minimap_p_y
		- (mini_map_range.start_y * scaled_tile_size), 5);
	draw_direction(game, &mini_map_range, CUB_SIZE / 2, 0x000000);
}
