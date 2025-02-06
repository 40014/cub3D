/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:42:28 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 12:50:36 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	player_new_pos_up(t_player_info *player_infos)
{
	double	move_speed;
	double	len_to_wall;

	move_speed = player_infos->move_speed;
	player_infos->real_angle = normalize_angle(player_infos->rotation_angle);
	if (check_around_pos(player_infos, &len_to_wall) == -1)
		return ;
	update_new_position(player_infos, 1, (DIS_WALL)-1, 0);
	if (len_to_wall <= DIS_WALL)
	{
		slide_on_the_wall(player_infos);
		return ;
	}
	if (len_to_wall - DIS_WALL < player_infos->move_speed)
	{
		update_position(player_infos, 1, len_to_wall - (DIS_WALL), 0);
		slide_on_the_wall(player_infos);
	}
	else if (len_to_wall >= player_infos->move_speed)
		update_position(player_infos, 1, move_speed, 0);
}

void	player_new_pos(t_player_info *player_infos)
{
	double	move_speed;
	double	len_to_wall;
	double	r_ang;

	move_speed = player_infos->move_speed;
	r_ang = fmod(player_infos->rotation_angle * (180 / M_PI) + 180, 360) * (M_PI
			/ 180);
	player_infos->real_angle = normalize_angle(r_ang);
	if (check_around_pos(player_infos, &len_to_wall) == -1)
		return ;
	update_new_position(player_infos, 0, (DIS_WALL)-1, 0);
	if (len_to_wall <= DIS_WALL)
	{
		slide_on_the_wall(player_infos);
		return ;
	}
	if (len_to_wall - DIS_WALL < player_infos->move_speed)
	{
		update_position(player_infos, 0, len_to_wall - DIS_WALL, 0);
		slide_on_the_wall(player_infos);
	}
	else if (len_to_wall >= player_infos->move_speed)
		update_position(player_infos, 0, move_speed, 0);
}

void	player_new_pos_right(t_player_info *player_infos)
{
	double	move_speed;
	double	len_to_wall;
	double	r_ang;

	move_speed = player_infos->move_speed;
	r_ang = fmod(player_infos->rotation_angle * (180 / M_PI) + 90, 360) * (M_PI
			/ 180);
	player_infos->real_angle = normalize_angle(r_ang);
	if (check_around_pos(player_infos, &len_to_wall) == -1)
		return ;
	update_new_position(player_infos, 1, (DIS_WALL)-1, M_PI / 2);
	if (len_to_wall <= DIS_WALL)
	{
		slide_on_the_wall(player_infos);
		return ;
	}
	if (len_to_wall - DIS_WALL < player_infos->move_speed)
	{
		update_position(player_infos, 1, len_to_wall - DIS_WALL, M_PI / 2);
		slide_on_the_wall(player_infos);
	}
	else if (len_to_wall >= player_infos->move_speed)
		update_position(player_infos, 1, move_speed, M_PI / 2);
}

void	player_new_pos_left(t_player_info *player_infos)
{
	double	move_speed;
	double	len_to_wall;
	double	r_ang;

	move_speed = player_infos->move_speed;
	r_ang = fmod(player_infos->rotation_angle * (180 / M_PI) + 270, 360) * (M_PI
			/ 180);
	player_infos->real_angle = normalize_angle(r_ang);
	if (check_around_pos(player_infos, &len_to_wall) == -1)
		return ;
	update_new_position(player_infos, 1, (DIS_WALL)-1, -(M_PI / 2));
	if (len_to_wall <= DIS_WALL)
	{
		slide_on_the_wall(player_infos);
		return ;
	}
	if (len_to_wall - DIS_WALL < player_infos->move_speed)
	{
		update_position(player_infos, 1, len_to_wall - DIS_WALL, -(M_PI / 2));
		slide_on_the_wall(player_infos);
	}
	else if (len_to_wall >= player_infos->move_speed)
		update_position(player_infos, 1, move_speed, -(M_PI / 2));
}

int	game_loop(t_base *game)
{
	if (game->s_keys->right)
		update_angle(game->player_infos, 1, game->player_infos->rotation_speed);
	if (game->s_keys->left)
		update_angle(game->player_infos, 0, game->player_infos->rotation_speed);
	if (game->s_keys->w)
		player_new_pos_up(game->player_infos);
	if (game->s_keys->s)
		player_new_pos(game->player_infos);
	if (game->s_keys->d)
		player_new_pos_right(game->player_infos);
	if (game->s_keys->a)
		player_new_pos_left(game->player_infos);
	if (game->s_keys->o)
		check_if_door(game->player_infos);
	if (game->mouse_left_pressed)
		update_angle(game->player_infos, 0, MOUSE_SPED);
	if (game->mouse_right_pressed)
		update_angle(game->player_infos, 1, MOUSE_SPED);
	if (game->weapon_sprite->is_animating)
		weapon_animation(game);
	do_the_magic(game);
	return (0);
}
