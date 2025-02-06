/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:42:18 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 12:53:21 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	check_edge(t_player_info *player_infos, int y, int x)
{
	if (player_infos->real_angle > (M_PI / 2) * 3
		|| (player_infos->real_angle > M_PI / 2
			&& player_infos->real_angle < M_PI))
	{
		y = (player_infos->wall_hit->nj - 10) / CUB_SIZE;
		x = (player_infos->wall_hit->ni - 10) / CUB_SIZE;
		if (player_infos->map[y][x] != '1')
			return (1);
		y = (player_infos->wall_hit->nj + 10) / CUB_SIZE;
		x = (player_infos->wall_hit->ni + 10) / CUB_SIZE;
		if (player_infos->map[y][x] != '1')
			return (1);
	}
	else
	{
		y = (player_infos->wall_hit->nj - 10) / CUB_SIZE;
		x = (player_infos->wall_hit->ni + 10) / CUB_SIZE;
		if (player_infos->map[y][x] != '1')
			return (1);
		y = (player_infos->wall_hit->nj + 10) / CUB_SIZE;
		x = (player_infos->wall_hit->ni - 10) / CUB_SIZE;
		if (player_infos->map[y][x] != '1')
			return (1);
	}
	return (0);
}

double	get_the_lenght(t_player_info *player_infos)
{
	int	d;

	player_infos->ray_rotation_angle = player_infos->real_angle;
	casting_rays(player_infos);
	if (player_infos->real_angle == 0 || player_infos->real_angle == M_PI / 2
		|| player_infos->real_angle == (M_PI / 2) * 3
		|| player_infos->real_angle == M_PI)
		return (player_infos->wall_hit->lenght);
	d = ray_angle_direction(player_infos);
	if (d == 1)
		player_infos->ray_rotation_angle = M_PI / 2;
	else if (d == 2)
		player_infos->ray_rotation_angle = (M_PI / 2) * 3;
	else if (d == 3)
		player_infos->ray_rotation_angle = M_PI;
	else if (d == 4)
		player_infos->ray_rotation_angle = 0;
	casting_rays(player_infos);
	return (player_infos->wall_hit->lenght);
}

double	get_the_lenght2(t_player_info *player_infos)
{
	int	d;

	player_infos->ray_rotation_angle = player_infos->real_angle;
	casting_rays(player_infos);
	if (check_edge(player_infos, 0, 0) == 1)
		return (player_infos->wall_hit->lenght);
	d = ray_angle_direction(player_infos);
	get_angle_from_side(player_infos, d);
	casting_rays(player_infos);
	return (player_infos->wall_hit->lenght);
}

double	check_around_pos(t_player_info *player_infos, double *len_to_wall)
{
	double	len_to_wall2;

	*len_to_wall = get_the_lenght(player_infos);
	len_to_wall2 = get_the_lenght2(player_infos);
	player_infos->ray_rotation_angle = player_infos->real_angle;
	casting_rays(player_infos);
	close_doors(player_infos);
	if (len_to_wall2 <= DIS_WALL
		&& player_infos->wall_hit->lenght <= (DIS_WALL) * 2)
		return (-1);
	if (player_infos->wall_hit->lenght < DIS_WALL)
		return (-1);
	if (player_infos->wall_hit->lenght < *len_to_wall)
		*len_to_wall = player_infos->wall_hit->lenght;
	return (*len_to_wall);
}
