/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_player_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:42:39 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 20:28:51 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	is_last_weapon_frame(t_sprite *weapon_sprite)
{
	return (weapon_sprite->current_frame >= weapon_sprite->frame_count);
}

void	weapon_animation(t_base *game)
{
	game->weapon_sprite->frame_timer++;
	if (game->weapon_sprite->frame_timer >= 5)
	{
		game->weapon_sprite->current_frame++;
		if (is_last_weapon_frame((game->weapon_sprite)))
		{
			game->weapon_sprite->current_frame = 0;
			game->weapon_sprite->is_animating = 0;
		}
		game->weapon_sprite->frame_timer = 0;
	}
}
