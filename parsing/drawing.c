/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:58:32 by medo              #+#    #+#             */
/*   Updated: 2025/01/06 15:59:40 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void my_mlx_pixel_put(t_base *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= SCREEN_SIZE || y < 0 || y >= SCREEN_HEIGHT)
        return;
    dst = game->mlx_ptrs->addr + (y * game->mlx_ptrs->line_length + x * (game->mlx_ptrs->bpp / 8));
    *(unsigned int *)dst = color;
}

// void my_mlx_pixel_put(t_base *game, int x, int y, int color)
// {
//     char *dst;

//     if (x < 0 || x >= game->map_width * CUB_SIZE || y < 0 || y >= game->map_height * CUB_SIZE)
//         return ;
//     dst = game->mlx_ptrs->addr + (y * game->mlx_ptrs->line_length + x * (game->mlx_ptrs->bpp / 8));
//     *(unsigned int *)dst = color;
// }

void draw_square(t_base *game, int x, int y, int color)
{
    int i, j;

    i = 0;
    while (i < CUB_SIZE)
    {
        j = 0;
        while (j < CUB_SIZE)
        {
            my_mlx_pixel_put(game, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_base *game)
{
    int i;
    int j;
    int y;
    int x;

    y = 0;
    i = 0;
    while (game->map[i])
    {
        x = 0;
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '1')
                draw_square(game, x, y, 0x0033FF33);
            else if (game->map[i][j] == '0')
                draw_square(game, x, y, 0xFFFFFF);
            else if (game->map[i][j] == ' ')
                draw_square(game, x, y, 0x00CC6633);
            else if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
                     game->map[i][j] == 'E' || game->map[i][j] == 'W')
                draw_square(game, x, y, 0xFFFFFF);
            j++;
            x = x + CUB_SIZE; // Move to the next tile position horizontally
        }
        i++;
        y = y + CUB_SIZE; // Move to the next tile position vertically
    }
}
 