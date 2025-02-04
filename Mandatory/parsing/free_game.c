/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:38:26 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/04 17:51:16 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_textures(t_base *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i])
		{
			if (game->textures[i]->img_ptr)
				mlx_destroy_image(game->mlx_ptrs->mlx_ptr,
					game->textures[i]->img_ptr);
			free(game->textures[i]);
			game->textures[i] = NULL;
		}
		i++;
	}
}

void	free_map2(t_base *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (game->player_infos->map2[i])
			free(game->player_infos->map2[i]);
		i++;
	}
	free(game->player_infos->map2);
}

void	free_map(t_base *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i])
			free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	exit_game(t_base *game)
{
	free_path(game);
	free(game->s_keys);
	free_textures(game);
	if (game->map)
		free_map(game);
	if (game->player_infos->map2)
		free_map2(game);
	if (game->mlx_ptrs->img)
		mlx_destroy_image(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->img);
	if (game->mlx_ptrs->win)
		mlx_destroy_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win);
	if (game->mlx_ptrs->mlx_ptr)
		mlx_destroy_display(game->mlx_ptrs->mlx_ptr);
	free(game->mlx_ptrs->mlx_ptr);
	exit(0);
}
