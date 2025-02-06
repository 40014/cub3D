/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:47:34 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 12:52:20 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	slide_on_the_wall(t_player_info *player_infos)
{
	int	x;
	int	y;

	get_the_real_hit_point(player_infos);
	y = (int)player_infos->j / CUB_SIZE;
	x = (int)player_infos->wall_hit->ni / CUB_SIZE;
	if (player_infos->map[y][x] != '1')
		player_infos->i = player_infos->new_i;
	y = (int)player_infos->wall_hit->nj / CUB_SIZE;
	x = (int)player_infos->i / CUB_SIZE;
	if (player_infos->map[y][x] != '1')
		player_infos->j = player_infos->new_j;
}

void	do_the_magic(t_base *game)
{
	rendering_3d(game);
	draw_minimap(game);
	draw_weapon_sprite(game, game->weapon_sprite);
	mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win,
		game->mlx_ptrs->img, 0, 0);
}
