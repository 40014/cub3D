#include "../cub.h"

void ft_draw_square(t_base *game, int x, int y, int color)
{
    int i;
    int j;
    int scale_size;

    scale_size = CUB_SIZE / MINI_MAP_SIZE;
    j = 0;
    while (j < scale_size)
    {
        i = 0;
        while (i < scale_size)
        {
            my_mlx_pixel_put(game, x + i, y + j, color);
            i++;
        }
        j++;
    }
}

void    draw_minimap_walls(t_base *game, t_mini_range *mini_map_range)
{
    int     i;
    int     j;
    int     scaled_tile_size;
    int     color;
    int     x;
    int     y;

    scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
    j = mini_map_range->start_y;
    while (j <= mini_map_range->end_y && j < game->map_height)
    {
        i = mini_map_range->start_i;
        while (i <= mini_map_range->end_i && i < game->map_width)
        {
            color = 0x009900FF;
            if (game->player_infos->map2[j][i] == '1')
                color = 0x000000;
            else if (game->player_infos->map2[j][i] == '0')
                color = 0xAAAAAA;
            else if (game->player_infos->map2[j][i] == 'D')
                color = 0xff8633;
            else if (game->player_infos->map2[j][i] == 'N' || game->player_infos->map2[j][i] == 'S' 
                || game->player_infos->map2[j][i] == 'W' || game->player_infos->map2[j][i] == 'E')
                color = 0xAAAAAA;
            x = (i - mini_map_range->start_i) * scaled_tile_size;
            y = (j - mini_map_range->start_y) * scaled_tile_size;
            ft_draw_square(game, x, y, color);
            i++;
        }
        j++;
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


void fix_start_end_i(t_mini_range *mini_map_range, t_base *game)
{
    if (mini_map_range->start_i < 0 && mini_map_range->end_i > game->map_width)
    {
        while (mini_map_range->start_i < 0)
            mini_map_range->start_i++;
        while (mini_map_range->end_i > game->map_width)
            mini_map_range->end_i--;
    }
    else if (mini_map_range->start_i < 0)
    {
        while (mini_map_range->start_i < 0)
        {
            mini_map_range->start_i++;
            if (mini_map_range->end_i < game->map_width)
                mini_map_range->end_i++;
        }
    }
    else if (mini_map_range->end_i > game->map_width)
    {
        while (mini_map_range->end_i > game->map_width)
        {
            mini_map_range->end_i--;
            if (mini_map_range->start_i > 0)
            mini_map_range->start_i--;
        }
    }
}

void fix_start_end_y(t_mini_range *mini_map_range, t_base *game)
{
    if (mini_map_range->start_y < 0 && mini_map_range->end_y > game->map_height)
    {
        while (mini_map_range->start_y < 0)
            mini_map_range->start_y++;
        while (mini_map_range->end_y > game->map_height)
            mini_map_range->end_y--;
    }
    else if (mini_map_range->start_y < 0)
    {
        while (mini_map_range->start_y < 0)
        {
            mini_map_range->start_y++;
            if (mini_map_range->end_y < game->map_height)
                mini_map_range->end_y++;
        }
    }
    else if (mini_map_range->end_y > game->map_height)
    {
        
        while (mini_map_range->end_y > game->map_height)
        {
            mini_map_range->end_y--;
            if (mini_map_range->start_y > 0)
                mini_map_range->start_y--;
        }
    }
}

void find_mini_map_range(t_mini_range *mini_map_range, t_base *game)
{
    int  scaled_tile_size;
    int i;
    int y;

    scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
    mini_map_range->minimap_p_x = game->player_infos->i / MINI_MAP_SIZE;
    mini_map_range->minimap_p_y = game->player_infos->j  / MINI_MAP_SIZE;
    i = (int)mini_map_range->minimap_p_x / scaled_tile_size;
    y = (int)mini_map_range->minimap_p_y / scaled_tile_size;
    mini_map_range->start_i = i - CELLS_RANGE;
    mini_map_range->end_i = i + CELLS_RANGE;
    mini_map_range->start_y = y - CELLS_RANGE;
    mini_map_range->end_y = y + CELLS_RANGE;
    fix_start_end_i(mini_map_range, game);
    fix_start_end_y(mini_map_range, game);   
}

void draw_direction(t_base *game,t_mini_range *mini_map_range, double line_lenght, int color)
{
    double x1;
    double y1;
    int x;
    int y;
    int  scaled_tile_size;

    scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;

    while(line_lenght >= 0)
    {
        x1 = mini_map_range->minimap_p_x  - (mini_map_range->start_i * scaled_tile_size ) + cos(game->player_infos->rotation_angle) * line_lenght;
        y1 = mini_map_range->minimap_p_y  - (mini_map_range->start_y * scaled_tile_size ) + sin(game->player_infos->rotation_angle) * line_lenght;
        my_mlx_pixel_put(game, x1, y1, color);
        line_lenght--;
    }
   
}


void draw_minimap(t_base *game)
{
    t_mini_range mini_map_range;
        int  scaled_tile_size;
    double saved_j;
    double saved_i;
    int saved_cub_size;

    scaled_tile_size = CUB_SIZE / MINI_MAP_SIZE;
    find_mini_map_range(&mini_map_range, game);
    draw_minimap_walls(game, &mini_map_range);
    draw_circle(game, mini_map_range.minimap_p_x - (mini_map_range.start_i * scaled_tile_size ),  mini_map_range.minimap_p_y - (mini_map_range.start_y * scaled_tile_size ), 5, 0xFF0000);
    draw_direction(game, &mini_map_range, CUB_SIZE / 2, 0x000000);

}