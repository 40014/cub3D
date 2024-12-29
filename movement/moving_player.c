#include "../cub.h"

void player_new_pos(t_player_info *player_infos)
{
    int x;
    int y;
    double move_speed;
    double len_to_wall;

    y = player_infos->new_j / CUB_SIZE;
    x = player_infos->new_i / CUB_SIZE;
    move_speed = player_infos->move_speed;
    player_infos->check_one_cub = 1;
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    len_to_wall = player_infos->wall_hit->lenght;
    if (len_to_wall < player_infos->move_speed)
    {
        player_infos->i = player_infos->i - cos(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j - sin(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
        
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
    
    player_infos->check_one_cub = 0;
}

void player_new_pos_up(t_player_info *player_infos)
{
    int x;
    int y;
    double move_speed;
    double len_to_wall;

    y = player_infos->new_j / CUB_SIZE;
    x = player_infos->new_i / CUB_SIZE;
    move_speed = player_infos->move_speed;
    player_infos->check_one_cub = 1;
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    len_to_wall = player_infos->wall_hit->lenght;
    if (len_to_wall < player_infos->move_speed)
    {
        player_infos->i = player_infos->i + cos(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j + sin(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
        
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
    
    player_infos->check_one_cub = 0;
}

void player_new_pos_right(t_player_info *player_infos)
{
    int x;
    int y;
    double move_speed;
    double len_to_wall;

    y = player_infos->new_j / CUB_SIZE;
    x = player_infos->new_i / CUB_SIZE;
    move_speed = player_infos->move_speed;
    player_infos->check_one_cub = 1;
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    len_to_wall = player_infos->wall_hit->lenght;
    if (len_to_wall < player_infos->move_speed)
    {
        player_infos->i = player_infos->i + cos(player_infos->rotation_angle + M_PI / 2) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j + sin(player_infos->rotation_angle + M_PI / 2) * (len_to_wall - DIS_WALL);
        
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
    
    player_infos->check_one_cub = 0;
}

void player_new_pos_left(t_player_info *player_infos)
{
    int x;
    int y;
    double move_speed;
    double len_to_wall;

    y = player_infos->new_j / CUB_SIZE;
    x = player_infos->new_i / CUB_SIZE;
    move_speed = player_infos->move_speed;
    player_infos->check_one_cub = 1;
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    len_to_wall = player_infos->wall_hit->lenght;
    if (len_to_wall < player_infos->move_speed)
    {
        player_infos->i = player_infos->i + cos(player_infos->rotation_angle - M_PI / 2) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j + sin(player_infos->rotation_angle - M_PI / 2) * (len_to_wall - DIS_WALL);
        
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
    
    player_infos->check_one_cub = 0;
}

int game_loop(t_base *game)
{
    int i;

    i = 0;
    if (game->s_keys->right)
    {
        game->player_infos->rotation_angle += game->player_infos->rotation_speed;
        if (game->player_infos->rotation_angle > 2 * M_PI)
            game->player_infos->rotation_angle -= 2 * M_PI;
        i = 1;
    }
    if (game->s_keys->left)
    {
        game->player_infos->rotation_angle -= game->player_infos->rotation_speed;
        if (game->player_infos->rotation_angle < 0)
            game->player_infos->rotation_angle += 2 * M_PI;
        i = 1;
    }

    // Move forward
    if (game->s_keys->w)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->real_angle = game->player_infos->rotation_angle;
        player_new_pos_up(game->player_infos);
        i = 1;
    }

    // Move backward
    if (game->s_keys->s)
    {
        game->player_infos->new_i = game->player_infos->i - cos(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j - sin(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->real_angle = fmod(game->player_infos->rotation_angle * (180 / M_PI) + 180, 360) * (M_PI / 180);
        player_new_pos(game->player_infos);
        i = 1;
    }

    // Move right
    if (game->s_keys->d)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle + M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle + M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->real_angle = fmod(game->player_infos->rotation_angle * (180 / M_PI) + 90, 360) * (M_PI / 180);
        player_new_pos_right(game->player_infos);
        i = 1;
    }

    // Move left
    if (game->s_keys->a)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle - M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle - M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->real_angle = fmod(game->player_infos->rotation_angle * (180 / M_PI) + 270, 360) * (M_PI / 180);
        player_new_pos_left(game->player_infos);
        i = 1 ;
    }
    if (i == 1)
    {
        draw_map(game);
        cast_rays(game);
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }
    return 0;
}


void get_player_pos(t_player_info *player_infos)
{
    int i;
    int j;

    j = 0;
    while(j < player_infos->map_height)
    {
        i = 0;
        while(i < player_infos->map_width)
        {
            if (player_infos->map[j][i] == 'N')
            {
                player_infos->i = (i + 0.5) * CUB_SIZE;
                player_infos->j = (j + 0.5) * CUB_SIZE;
                return;
            }
            i++;
        }
        j++;
    }
}