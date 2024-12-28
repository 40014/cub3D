#include "../cub.h"

void player_new_pos(t_player_info *player_infos)
{
    int x;
    int y;
    double move_speed;
    double x1;
    double y1;

    y = player_infos->new_j / CUB_SIZE;
    x = player_infos->new_i / CUB_SIZE;
    move_speed = player_infos->move_speed;
    if (player_infos->map[y][x] == '1')
    {
        while(move_speed > 0)
        {
            x1 = player_infos->i + cos(player_infos->rotation_angle ) * (move_speed * -1);
            y1 = player_infos->j + sin(player_infos->rotation_angle ) * (move_speed * -1);
            y = y1 / CUB_SIZE;
            x = x1 / CUB_SIZE;
            if(player_infos->map[y][x] != '1')
            {
               
                player_infos->i = x1;
                player_infos->j = y1;
                return ; 
            }
            move_speed -= 0.1;
        }
    }
    else
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
}

void player_new_pos_up(t_player_info *player_infos)
{
    int x;
    int y;
    double move_speed;
    double x1;
    double y1;
    int lenght_to_wall;

    y = player_infos->new_j / CUB_SIZE;
    x = player_infos->new_i / CUB_SIZE;
    move_speed = player_infos->move_speed;
    if (player_infos->map[y][x] == '1')
    {
        while (move_speed > 0)
        {
            x1 = player_infos->i + cos(player_infos->rotation_angle) * (move_speed);
            y1 = player_infos->j + sin(player_infos->rotation_angle ) * (move_speed);
            y = (int)y1 / CUB_SIZE;
            x = (int)x1 / CUB_SIZE;
            if (player_infos->map[y][x] != '1')
            {
                player_infos->i = x1;
                player_infos->j = y1;
                return;
            }
            move_speed -= 0.1; 
        }
    }
    else
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
}


int game_loop(t_base *game)
{
    if (game->s_keys->right)
    {
        game->player_infos->rotation_angle += game->player_infos->rotation_speed * 1;
        if (game->player_infos->rotation_angle > (360 * (M_PI / 180)))
              game->player_infos->rotation_angle -= 360 * (M_PI / 180);
        draw_map(game);
        cast_rays(game);
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }
    if(game->s_keys->left)
    {
        game->player_infos->rotation_angle += game->player_infos->rotation_speed * (-1);
        if (game->player_infos->rotation_angle < 0)
              game->player_infos->rotation_angle += 360 * (M_PI / 180);
        draw_map(game);
        cast_rays(game);
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }
    if (game->s_keys->w)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        player_new_pos_up(game->player_infos);
        draw_map(game);
        
        cast_rays(game);
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }
    if (game->s_keys->s)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle) * (game->player_infos->move_speed * -1);
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle) * (game->player_infos->move_speed * -1);
        player_new_pos(game->player_infos);
        draw_map(game);
        cast_rays(game);
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }
    if (game->s_keys->d)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle + M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle + M_PI / 2) * game->player_infos->move_speed;
        if (game->player_infos->map[(int)(game->player_infos->new_j / CUB_SIZE)][(int)(game->player_infos->new_i / CUB_SIZE)] != '1')
            player_new_pos_up(game->player_infos);
        draw_map(game);
        cast_rays(game);
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }

    if (game->s_keys->a)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle - M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle - M_PI / 2) * game->player_infos->move_speed;
        if (game->player_infos->map[(int)(game->player_infos->new_j / CUB_SIZE)][(int)(game->player_infos->new_i / CUB_SIZE)] != '1')
            player_new_pos(game->player_infos);
        draw_map(game);
        cast_rays(game);
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }   
    return(0);
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