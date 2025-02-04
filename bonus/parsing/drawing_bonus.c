/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:58:32 by medo              #+#    #+#             */
/*   Updated: 2025/02/04 14:42:10 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	my_mlx_pixel_put(t_base *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_SIZE || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = game->mlx_ptrs->addr + (y * game->mlx_ptrs->line_length + x
			* (game->mlx_ptrs->bpp / 8));
	*(unsigned int *)dst = color;
}
