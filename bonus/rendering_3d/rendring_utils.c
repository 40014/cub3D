/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:58 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 15:51:56 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

double	calculate_wall_x(t_player_info *ray)
{
	double	wall_x;

	if (ray->wall_hit->hit_direction == 0)
		wall_x = fmod(ray->wall_hit->ni, CUB_SIZE);
	else
		wall_x = fmod(ray->wall_hit->nj, CUB_SIZE);
	return (wall_x);
}

int	get_texture_index(t_player_info *player_infos, int n)
{
	int	x;
	int	y;

	n = ray_angle_direction(player_infos) - 1;
	get_the_real_hit_point(player_infos);
	y = (int)player_infos->wall_hit->nj / CUB_SIZE;
	x = (int)player_infos->wall_hit->ni / CUB_SIZE;
	if (player_infos->map2[y][x] == 'D')
		return (4);
	return (n);
}

int	get_texture_x(t_base *game, double wall_x, int n)
{
	int			tex_x;
	t_texture	*texture;

	texture = game->textures[n];
	tex_x = (int)(wall_x * ((double)texture->width / TILE_SIZE));
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

double	get_wall_height(t_player_info *player_infos, double distance_projection)
{
	double	correct_lenght;
	double	wall_height;
	double	norml_a;

	norml_a = normalize_angle(player_infos->ray_rotation_angle);
	player_infos->ray_rotation_angle = norml_a;
	casting_rays(player_infos);
	correct_lenght = player_infos->wall_hit->lenght
		* cos(player_infos->ray_rotation_angle - player_infos->rotation_angle);
	wall_height = (CUB_SIZE / correct_lenght) * distance_projection;
	return (wall_height);
}
