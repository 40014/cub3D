/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:15 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/03 13:01:51 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	handle_up_key(t_base *game)
{
	if (!game->weapon_sprite->is_animating)
	{
		game->weapon_sprite->is_animating = 1;
		game->weapon_sprite->current_frame = 1;
		game->weapon_sprite->frame_timer = 0;
	}
}

int	key_press(int keycode, t_base *game)
{
	if (keycode == ESC)
		exit_game(game);
	if (keycode == W_KEY)
		game->s_keys->w = 1;
	else if (keycode == A_KEY)
		game->s_keys->a = 1;
	else if (keycode == S_KEY)
		game->s_keys->s = 1;
	else if (keycode == D_KEY)
		game->s_keys->d = 1;
	else if (keycode == LEFT_ARROW)
		game->s_keys->left = 1;
	else if (keycode == RIGHT_ARROW)
		game->s_keys->right = 1;
	else if (keycode == O_KEY)
		game->s_keys->o = 1;
	else if (keycode == UP)
		handle_up_key(game);
	return (0);
}

int	key_release(int keycode, t_base *game)
{
	if (keycode == W_KEY)
		game->s_keys->w = 0;
	else if (keycode == A_KEY)
		game->s_keys->a = 0;
	else if (keycode == S_KEY)
		game->s_keys->s = 0;
	else if (keycode == D_KEY)
		game->s_keys->d = 0;
	else if (keycode == LEFT_ARROW)
		game->s_keys->left = 0;
	else if (keycode == RIGHT_ARROW)
		game->s_keys->right = 0;
	else if (keycode == O_KEY)
		game->s_keys->o = 0;
	return (0);
}

int	mouse_press(int button, int x, int y, t_base *game)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		game->mouse_left_pressed = 1;
	else if (button == MOUSE_RIGHT)
		game->mouse_right_pressed = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_base *game)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		game->mouse_left_pressed = 0;
	else if (button == MOUSE_RIGHT)
		game->mouse_right_pressed = 0;
	return (0);
}
