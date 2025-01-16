#include "../cub.h"

void ft_draw_square(t_base *game, int x, int y, int color)
{
    int i;
    int j;
    int scale_size;

    scale_size = CUB_SIZE / MINI_MAP_SIZE;
    i = 0;
    while (i < scale_size)
    {
        j = 0;
        while (j < scale_size)
        {
            my_mlx_pixel_put(game, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void    draw_minimap_walls(t_base *game, int start_x, int start_y)
{
    int     i;
    int     j;
    int     scaled_tile_size;
    int     color;
    int     x;
    int     y;

    scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            color = 0x009900FF;
            if (game->map[i][j] == '1')
                color = 0x000000;
            else if (game->map[i][j] == '0')
                color = 0xAAAAAA;
            else if (game->map[i][j] == 'N')
                color = 0xAAAAAA;
            x = j * scaled_tile_size;
            y = i * scaled_tile_size;
            
            ft_draw_square(game, x, y, color);
            j++;
        }
        i++;
    }
}

void draw_circle(t_base *game, double center_x, double center_y, int radius, int color)
{
    int     x;
    int     y;
    int     radius_squared;

    radius_squared = radius * radius;
    y = -radius;
    while ( y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= radius_squared)
                my_mlx_pixel_put(game, center_x + x, center_y + y, color);
            x++;
        }
        y++;
    }
}


void draw_minimap_player(t_base *game, int start_x, int start_y)
{
    int scaled_tile_size;
    int player_x;
    int player_y;
    int radius;

    scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
    game->s_keys->minimap_p_x = game->player_infos->i / MINI_MAP_SIZE;
    game->s_keys->minimap_p_y = game->player_infos->j  / MINI_MAP_SIZE;
    
    radius = scaled_tile_size / MINI_MAP_SIZE_PLAYER; 

    draw_circle(game, game->s_keys->minimap_p_x, game->s_keys->minimap_p_y, radius, 0xFF0000);
}

void draw_minimap(t_base *game)
{
    draw_minimap_walls(game, 0, 0);
    draw_minimap_player(game, 0, 0);
}
