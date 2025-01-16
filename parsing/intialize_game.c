/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:52:51 by medo              #+#    #+#             */
/*   Updated: 2025/01/06 16:53:11 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_init_struct_game(t_base *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->fd = -1;
	game->map = NULL;
	game->readmap = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->player_dir = 0;
	game->player_x = -1;
	game->player_y = -1;
	game->floor_color = -1;
	game->ceiling_color = -1;
	while (j < 4)
    {
        game->path[j] = NULL;
        j++;
    }
    while (i < 4)
    {
        game->textures[i] = malloc(sizeof(t_texture));
        if (!game->textures[i])
        {
            ft_printf_err("Error\nFailed to allocate memory for texture \n");
            exit(1);
        }
        i++;
    }
}

void	initialize_map(t_base *game, char *line)
{
	game->map = malloc(sizeof(char *) * 2);
	game->map[0] = ft_strdup(line);
	game->map[1] = NULL;
	game->map_height = 1;
	game->map_width = ft_strlen2(line);
}

int	key_press(int keycode, t_base *game)
{
	if (keycode == ESC)
		exit(0);
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
	return (0);
}

void	initialize_keys(t_base *game)
{
	game->s_keys = malloc(sizeof(t_keys));
	if (!game->s_keys)
	{
		perror("Error allocating memory for keys");
		exit(1);
	}
	game->s_keys->w = 0;
	game->s_keys->s = 0;
	game->s_keys->a = 0;
	game->s_keys->d = 0;
	game->s_keys->left = 0;
	game->s_keys->right = 0;
	game->s_keys->minimap_p_x = 0;
	game->s_keys->minimap_p_y = 0;
}
