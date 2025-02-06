/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inters_down_left.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:53:36 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 18:56:16 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	check_the_edge2(t_player_info *player_infos, int j, int i)
{
	int	y;
	int	x;

	if (i <= 0 || j <= 0)
		return (0);
	y = j / CUB_SIZE;
	x = i / CUB_SIZE;
	if ((out_map(player_infos, x, y) == 0))
	{
		y = (j - 2) / CUB_SIZE;
		x = (i - 2) / CUB_SIZE;
		if (player_infos->map[y][x] != '1')
			return (0);
		y = (j + 2) / CUB_SIZE;
		x = (i + 2) / CUB_SIZE;
		if (player_infos->map[y][x] != '1')
			return (0);
		player_infos->wall_hit->in_edge = 1;
		return (1);
	}
	return (0);
}

void	find_inters_down_left_h(t_player_info *player_infos, int y, int x)
{
	double	isteps;
	double	jsteps;

	jsteps = ((int)player_infos->j / CUB_SIZE) * CUB_SIZE + CUB_SIZE;
	isteps = player_infos->i - (jsteps - player_infos->j)
		/ fabs(tan(player_infos->ray_rotation_angle));
	y = ((int)jsteps) / CUB_SIZE;
	x = ((int)isteps) / CUB_SIZE;
	if (((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
		|| check_the_edge2(player_infos, jsteps, isteps) == 1)
	{
		player_infos->wall_hit->hi = isteps;
		player_infos->wall_hit->hj = jsteps;
		return ;
	}
	while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1'
		&& check_the_edge2(player_infos, jsteps, isteps) != 1)
	{
		jsteps += CUB_SIZE;
		isteps -= CUB_SIZE / fabs(tan(player_infos->ray_rotation_angle));
		y = ((int)jsteps) / CUB_SIZE;
		x = ((int)isteps) / CUB_SIZE;
	}
	if (out_map(player_infos, x, y) == 0)
		apply_values(player_infos, jsteps, isteps, 'h');
}

void	find_inters_down_left_v(t_player_info *player_infos, int y, int x)
{
	double	isteps;
	double	jsteps;

	isteps = ((int)player_infos->i / CUB_SIZE) * CUB_SIZE;
	jsteps = player_infos->j + ((player_infos->i - isteps)
			* fabs(tan(player_infos->ray_rotation_angle)));
	y = ((int)jsteps) / CUB_SIZE;
	x = ((int)isteps - 1) / CUB_SIZE;
	if (((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
		|| check_the_edge2(player_infos, jsteps, isteps) == 1)
	{
		player_infos->wall_hit->vi = isteps;
		player_infos->wall_hit->vj = jsteps;
		return ;
	}
	while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1'
		&& check_the_edge2(player_infos, jsteps, isteps) != 1)
	{
		isteps -= CUB_SIZE;
		jsteps += CUB_SIZE * fabs(tan(player_infos->ray_rotation_angle));
		y = ((int)jsteps) / CUB_SIZE;
		x = (((int)isteps) - 1) / CUB_SIZE;
	}
	if (out_map(player_infos, x, y) == 0)
		apply_values(player_infos, jsteps, isteps, 'v');
}

void	find_nearest_wal_hit_down_left(t_player_info *player_infos)
{
	if (player_infos->wall_hit->hi == -1 || player_infos->wall_hit->hj == -1)
	{
		player_infos->wall_hit->nj = player_infos->wall_hit->vj;
		player_infos->wall_hit->ni = player_infos->wall_hit->vi;
		player_infos->wall_hit->hit_direction = 1;
	}
	else if (player_infos->wall_hit->vi == -1
		|| player_infos->wall_hit->vj == -1)
	{
		player_infos->wall_hit->nj = player_infos->wall_hit->hj;
		player_infos->wall_hit->ni = player_infos->wall_hit->hi;
	}
	else if (player_infos->wall_hit->hj < player_infos->wall_hit->vj
		&& player_infos->wall_hit->hi > player_infos->wall_hit->vi)
	{
		player_infos->wall_hit->nj = player_infos->wall_hit->hj;
		player_infos->wall_hit->ni = player_infos->wall_hit->hi;
	}
	else
	{
		player_infos->wall_hit->nj = player_infos->wall_hit->vj;
		player_infos->wall_hit->ni = player_infos->wall_hit->vi;
		player_infos->wall_hit->hit_direction = 1;
	}
}
