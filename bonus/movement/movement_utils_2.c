/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:42:21 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 12:46:08 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	get_angle_from_side(t_player_info *player_infos, int d)
{
	if (d == 1 || d == 2)
	{
		if (d == 1 && player_infos->ray_rotation_angle > M_PI / 2)
			player_infos->ray_rotation_angle = M_PI;
		if (d == 2 && player_infos->ray_rotation_angle < (M_PI / 2) * 3)
			player_infos->ray_rotation_angle = M_PI;
		else
			player_infos->ray_rotation_angle = 0;
	}
	else if (d == 3 || d == 4)
	{
		if (d == 3 && player_infos->ray_rotation_angle > M_PI)
			player_infos->ray_rotation_angle = (M_PI / 2) * 3;
		if (d == 4 && player_infos->ray_rotation_angle > (M_PI / 2) * 3)
			player_infos->ray_rotation_angle = (M_PI / 2) * 3;
		else
			player_infos->ray_rotation_angle = M_PI / 2;
	}
}

int	check_if_door(t_player_info *player_infos)
{
	int	y;
	int	x;
	int	d;
	int	c;

	c = 0;
	d = angle_direction(player_infos);
	y = (int)player_infos->j / CUB_SIZE;
	x = (int)player_infos->i / CUB_SIZE;
	if (player_infos->map2[y + 1][x] == 'D' && d == 1)
		player_infos->map[y + 1][x] = '0';
	else if (player_infos->map2[y - 1][x] == 'D' && d == 2)
		player_infos->map[y - 1][x] = '0';
	else if (player_infos->map2[y][x - 1] == 'D' && d == 3)
		player_infos->map[y][x - 1] = '0';
	else if (player_infos->map2[y][x + 1] == 'D' && d == 4)
		player_infos->map[y][x + 1] = '0';
	else
		c = 1;
	return (c);
}

void	update_new_position(t_player_info *player_infos, int sign, double speed,
		double angle)
{
	if (P_SPEED < speed)
		speed = P_SPEED;
	if (sign == 1)
	{
		player_infos->new_i = player_infos->i + cos(player_infos->rotation_angle
				+ angle) * speed;
		player_infos->new_j = player_infos->j + sin(player_infos->rotation_angle
				+ angle) * speed;
	}
	else
	{
		player_infos->new_i = player_infos->i
			- cos(player_infos->rotation_angle) * speed;
		player_infos->new_j = player_infos->j
			- sin(player_infos->rotation_angle) * speed;
	}
}

void	update_position(t_player_info *player_infos, int sign, double speed,
		double angle)
{
	if (sign == 1)
	{
		player_infos->i = player_infos->i + cos(player_infos->rotation_angle
				+ angle) * speed;
		player_infos->j = player_infos->j + sin(player_infos->rotation_angle
				+ angle) * speed;
	}
	else
	{
		player_infos->i = player_infos->i - cos(player_infos->rotation_angle)
			* speed;
		player_infos->j = player_infos->j - sin(player_infos->rotation_angle)
			* speed;
	}
}

void	update_angle(t_player_info *player_infos, int sign, double angle)
{
	if (sign == 1)
	{
		angle += player_infos->rotation_angle;
		player_infos->rotation_angle = normalize_angle(angle);
	}
	else
	{
		angle = player_infos->rotation_angle - angle;
		player_infos->rotation_angle = normalize_angle(angle);
	}
}
