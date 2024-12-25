#include "cub3D.h"

void move_player(t_base *game)
{
    float   move_speed = 1;
    int     prev_x;
    int     prev_y;

    prev_x = game->player_x;
    prev_y = game->player_y;
    if (game->s_keys->w && game->map[game->player_y - 1][game->player_x] == '0')
        game->player_y -= move_speed;
    if (game->s_keys->s && game->map[game->player_y + 1][game->player_x] == '0')
        game->player_y += move_speed;
    if (game->s_keys->a && game->map[game->player_y][game->player_x - 1] == '0')
        game->player_x -= move_speed;
    if (game->s_keys->d && game->map[game->player_y][game->player_x + 1] == '0')
        game->player_x += move_speed;

    // if (game->s_keys->left)
        // what should do if i click left key
    // if (game->s_keys->right)
        // what should do if i click right key
    if (prev_x != game->player_x || prev_y != game->player_y)
    {
        game->map[prev_y][prev_x] = '0';
        game->map[game->player_y][game->player_x] = game->player_dir;
    }
}


int game_loop(t_base *game)
{
    move_player(game);
    draw_map(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}
