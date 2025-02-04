/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:33:10 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/04 14:42:36 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	error_map_close(t_base *game)
{
	ft_printf_err("Error\nMap is not closed\n");
	free_split(game->map);
	free_texture(game->textures);
	free_path(game);
	exit(1);
}

void	error_of_door(t_base *game)
{
	ft_printf_err("Error\n");
	ft_printf_err("The door should be surrounded by at least two walls\n");
	free_split(game->map);
	free_texture(game->textures);
	free_path(game);
	exit(1);
}
