/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:15 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/04 18:26:03 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
