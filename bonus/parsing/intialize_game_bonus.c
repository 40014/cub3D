/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:52:51 by medo              #+#    #+#             */
/*   Updated: 2025/02/04 14:42:29 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	init_path_and_textures(t_base *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 5)
	{
		game->path[j] = NULL;
		j++;
	}
	while (i < 5)
	{
		game->textures[i] = malloc(sizeof(t_texture));
		if (!game->textures[i])
		{
			ft_printf_err("Error\n");
			ft_printf_err("Failed to allocate memory for texture struct\n");
			exit(1);
		}
		game->textures[i]->img_ptr = NULL;
		game->textures[i]->data = NULL;
		i++;
	}
}

void	ft_init_struct_game(t_base *game)
{
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
	game->check_NO = 0;
	game->check_SO = 0;
	game->check_WE = 0;
	game->check_EA = 0;
	game->check_F = 0;
	game->check_C = 0;
	game->check_D1 = 0;
	init_path_and_textures(game);
}

void	initialize_map(t_base *game, char *line)
{
	game->map = malloc(sizeof(char *) * 2);
	game->map[0] = ft_strdup(line);
	game->map[1] = NULL;
	game->map_height = 1;
	game->map_width = ft_strlen2(line);
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
	game->s_keys->o = 0;
	game->s_keys->left = 0;
	game->s_keys->right = 0;
	game->mouse_left_pressed = 0;
	game->mouse_right_pressed = 0;
}
