/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:33:10 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/04 22:01:31 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	error_map_close(t_base *game)
{
	ft_printf_err("Error\nMap is not closed\n");
	free_split(game->map);
	free_texture(game->textures);
	free_path(game);
	exit(1);
}

void error_texture_exit(t_base *game)
{
    free_path(game);
    free_textures(game);
    if (game->map)
        free_map(game);
    if (game->mlx_ptrs->img)
        mlx_destroy_image(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->img);
    if (game->mlx_ptrs->win)
        mlx_destroy_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win);
    if (game->mlx_ptrs->mlx_ptr)
        mlx_destroy_display(game->mlx_ptrs->mlx_ptr);
    free(game->mlx_ptrs->mlx_ptr);
}
