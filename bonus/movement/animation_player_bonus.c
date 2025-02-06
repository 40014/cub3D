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
