/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:53:32 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 18:56:56 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	check_straight_ray(t_player_info *player_infos, double angle_of_ray)
{
	if (angle_of_ray == 0)
	{
		find_inters_right(player_infos);
		calculate_length(player_infos, player_infos->wall_hit->ni,
			player_infos->j);
	}
	else if (angle_of_ray == M_PI / 2)
	{
		find_inters_down(player_infos);
		calculate_length(player_infos, player_infos->i,
			player_infos->wall_hit->nj);
	}
	else if (angle_of_ray == M_PI)
	{
		find_inters_left(player_infos);
		calculate_length(player_infos, player_infos->wall_hit->ni,
			player_infos->j);
	}
	else if (angle_of_ray == 3 * M_PI / 2)
	{
		find_inters_up(player_infos);
		calculate_length(player_infos, player_infos->i,
			player_infos->wall_hit->nj);
	}
}

int	check_down_inters(t_player_info *player_infos)
{
	double	angle_of_ray;

	angle_of_ray = player_infos->ray_rotation_angle;
	if (angle_of_ray > 0 && angle_of_ray < M_PI / 2)
	{
		find_inters_down_right_h(player_infos, 0, 0);
		find_inters_down_right_v(player_infos, 0, 0);
		find_nearest_wal_hit_down_right(player_infos);
		calculate_length(player_infos, player_infos->wall_hit->ni,
			player_infos->wall_hit->nj);
		return (1);
	}
	else if (angle_of_ray > M_PI / 2 && angle_of_ray < M_PI)
	{
		find_inters_down_left_h(player_infos, 0, 0);
		find_inters_down_left_v(player_infos, 0, 0);
		find_nearest_wal_hit_down_left(player_infos);
		calculate_length(player_infos, player_infos->wall_hit->ni,
			player_infos->wall_hit->nj);
		return (1);
	}
	return (0);
}

int	check_up_inters(t_player_info *player_infos)
{
	double	angle_of_ray;

	angle_of_ray = player_infos->ray_rotation_angle;
	if (angle_of_ray > M_PI && angle_of_ray < 3 * M_PI / 2)
	{
		find_inters_up_left_h(player_infos, 0, 0);
		find_inters_up_left_v(player_infos, 0, 0);
		find_nearest_wal_hit_up_left(player_infos);
		calculate_length(player_infos, player_infos->wall_hit->ni,
			player_infos->wall_hit->nj);
		return (1);
	}
	else if (angle_of_ray > 3 * M_PI / 2 && angle_of_ray < 2 * M_PI)
	{
		find_inters_up_right_h(player_infos, 0, 0);
		find_inters_up_right_v(player_infos, 0, 0);
		find_nearest_wal_hit_up_right(player_infos);
		calculate_length(player_infos, player_infos->wall_hit->ni,
			player_infos->wall_hit->nj);
		return (1);
	}
	return (0);
}

void	casting_rays(t_player_info *player_infos)
{
	double	angle_of_ray;

	player_infos->wall_hit->vi = -1;
	player_infos->wall_hit->vj = -1;
	player_infos->wall_hit->hi = -1;
	player_infos->wall_hit->hj = -1;
	player_infos->wall_hit->hit_direction = 0;
	angle_of_ray = player_infos->ray_rotation_angle;
	if (check_up_inters(player_infos) == 1)
		return ;
	if (check_down_inters(player_infos) == 1)
		return ;
	check_straight_ray(player_infos, angle_of_ray);
}
