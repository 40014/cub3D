/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inters_straight.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:53:41 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 12:53:42 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	find_inters_right(t_player_info *player_infos)
{
	int		y;
	int		x;
	double	isteps;

	player_infos->wall_hit->hit_direction = 1;
	isteps = ((int)player_infos->i / CUB_SIZE) * CUB_SIZE + CUB_SIZE;
	y = ((int)player_infos->j) / CUB_SIZE;
	x = ((int)isteps) / CUB_SIZE;
	if ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
	{
		player_infos->wall_hit->ni = isteps;
		player_infos->wall_hit->nj = player_infos->j;
		return ;
	}
	while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1')
	{
		isteps += CUB_SIZE;
		y = ((int)player_infos->j) / CUB_SIZE;
		x = ((int)isteps) / CUB_SIZE;
	}
	if (out_map(player_infos, x, y) == 0)
	{
		player_infos->wall_hit->ni = isteps;
		player_infos->wall_hit->nj = player_infos->j;
	}
}

void	find_inters_down(t_player_info *player_infos)
{
	int		y;
	int		x;
	double	jsteps;

	jsteps = ((int)player_infos->j / CUB_SIZE) * CUB_SIZE + CUB_SIZE;
	x = ((int)player_infos->i) / CUB_SIZE;
	y = ((int)jsteps) / CUB_SIZE;
	if ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
	{
		player_infos->wall_hit->nj = jsteps;
		player_infos->wall_hit->ni = player_infos->i;
		return ;
	}
	while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1')
	{
		jsteps += CUB_SIZE;
		x = ((int)player_infos->i) / CUB_SIZE;
		y = ((int)jsteps) / CUB_SIZE;
	}
	if (out_map(player_infos, x, y) == 0)
	{
		player_infos->wall_hit->nj = jsteps;
		player_infos->wall_hit->ni = player_infos->i;
	}
}

void	find_inters_left(t_player_info *player_infos)
{
	int		y;
	int		x;
	double	isteps;

	player_infos->wall_hit->hit_direction = 1;
	isteps = ((int)player_infos->i / CUB_SIZE) * CUB_SIZE;
	y = ((int)player_infos->j) / CUB_SIZE;
	x = ((int)isteps - 1) / CUB_SIZE;
	if ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
	{
		player_infos->wall_hit->ni = isteps;
		player_infos->wall_hit->nj = player_infos->j;
		return ;
	}
	while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1')
	{
		isteps -= CUB_SIZE;
		y = ((int)player_infos->j) / CUB_SIZE;
		x = ((int)isteps - 1) / CUB_SIZE;
	}
	if (out_map(player_infos, x, y) == 0)
	{
		player_infos->wall_hit->ni = isteps;
		player_infos->wall_hit->nj = player_infos->j;
	}
}

void	find_inters_up(t_player_info *player_infos)
{
	int		y;
	int		x;
	double	jsteps;

	jsteps = ((int)player_infos->j / CUB_SIZE) * CUB_SIZE;
	x = ((int)player_infos->i) / CUB_SIZE;
	y = ((int)jsteps - 1) / CUB_SIZE;
	if ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
	{
		player_infos->wall_hit->nj = jsteps;
		player_infos->wall_hit->ni = player_infos->i;
		return ;
	}
	while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1')
	{
		jsteps -= CUB_SIZE;
		x = ((int)player_infos->i) / CUB_SIZE;
		y = ((int)jsteps - 1) / CUB_SIZE;
	}
	if (out_map(player_infos, x, y) == 0)
	{
		player_infos->wall_hit->nj = jsteps;
		player_infos->wall_hit->ni = player_infos->i;
	}
}
