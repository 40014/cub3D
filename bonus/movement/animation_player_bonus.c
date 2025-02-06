/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_player_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:42:39 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 15:42:40 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	weapon_animation(t_base *game)
{
	game->weapon_sprite->frame_timer++;
	if (game->weapon_sprite->frame_timer >= 5)
	{
		game->weapon_sprite->current_frame++;
		if (game->weapon_sprite->current_frame >= game->weapon_sprite->frame_count)
		{
			game->weapon_sprite->current_frame = 0;
			game->weapon_sprite->is_animating = 0;
		}
		game->weapon_sprite->frame_timer = 0;
	}
}
