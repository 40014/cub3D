#include "../cub.h"


// void slide_on_the_wall(t_player_info *player_infos)
// {
//     int x;
//     int y;

//     y = (int)player_infos->j / CUB_SIZE;
//     x = (int)player_infos->new_i / CUB_SIZE;
//     if (player_infos->map[y][x] != '1')
//         player_infos->i = player_infos->new_i;
//     y = (int) player_infos->new_j / CUB_SIZE;
//     x = (int) player_infos->i / CUB_SIZE;
//     if (player_infos->map[y][x] != '1')
//         player_infos->j = player_infos->new_j;
// }
void slide_on_the_wall(t_player_info *player_infos)
{
    int x;
    int y;

    if (player_infos->wall_hit->hit_direction == 0)
    {
       
        if (player_infos->ray_rotation_angle > 0 && player_infos->ray_rotation_angle < M_PI)
            player_infos->wall_hit->nj;
        else
            player_infos->wall_hit->nj -= 1;
    }       
    else
    {
        if (player_infos->ray_rotation_angle > M_PI / 2 && player_infos->ray_rotation_angle < 3 * (M_PI / 2))
            player_infos->wall_hit->ni -= 1;
    }
    y = (int)player_infos->j / CUB_SIZE;
    x = (int)player_infos->wall_hit->ni / CUB_SIZE;
    if (player_infos->map[y][x] != '1')
        player_infos->i = player_infos->new_i;
    y = (int) player_infos->wall_hit->nj / CUB_SIZE;
    x = (int) player_infos->i / CUB_SIZE;
    if (player_infos->map[y][x] != '1')
        player_infos->j = player_infos->new_j;
}

int check_edge(t_player_info *player_infos)
{
    int x;
    int y;

    if (player_infos->real_angle > (M_PI / 2) * 3 
    || (player_infos->real_angle > M_PI / 2 && player_infos->real_angle < M_PI))
    {
        y = (player_infos->wall_hit->nj - 10) / CUB_SIZE;
        x = (player_infos->wall_hit->ni - 10) / CUB_SIZE;
        if (player_infos->map[y][x] != '1')
            return(1);
        y = (player_infos->wall_hit->nj + 10) / CUB_SIZE;
        x = (player_infos->wall_hit->ni + 10) / CUB_SIZE;
        if (player_infos->map[y][x] != '1')
            return(1);
    }
    else 
    {
        y = (player_infos->wall_hit->nj - 10) / CUB_SIZE;
        x = (player_infos->wall_hit->ni+ 10) / CUB_SIZE;
        if (player_infos->map[y][x] != '1')
            return(1);
        y = (player_infos->wall_hit->nj + 10) / CUB_SIZE;
        x = (player_infos->wall_hit->ni- 10) / CUB_SIZE;
        if (player_infos->map[y][x] != '1')
            return(1);
        player_infos->wall_hit->in_edge = 1;
    }
    return(0);

}

double get_the_lenght(t_player_info *player_infos)
{

    find_wall_hit_h_v(player_infos);
    if (player_infos->real_angle == 0 || player_infos->real_angle == M_PI / 2 
        || player_infos->real_angle == (M_PI / 2) * 3 || player_infos->real_angle == M_PI )
        return(player_infos->wall_hit->lenght);
    if (player_infos->wall_hit->hit_direction == 0)
    {
        if (player_infos->ray_rotation_angle > 0 && player_infos->ray_rotation_angle < M_PI)
        {
            player_infos->ray_rotation_angle = M_PI / 2;
            find_wall_hit_h_v(player_infos);
        }
        else
        {
            player_infos->ray_rotation_angle = (M_PI / 2) * 3;
            find_wall_hit_h_v(player_infos);
        }
    }       
    else
    {
        if (player_infos->ray_rotation_angle > M_PI / 2 && player_infos->ray_rotation_angle < 3 * (M_PI / 2))
        {
            player_infos->ray_rotation_angle = M_PI;
            find_wall_hit_h_v(player_infos);
        }
        else
        {
            player_infos->ray_rotation_angle = 0;
            find_wall_hit_h_v(player_infos);
        }
    }
    return(player_infos->wall_hit->lenght);

}



double get_the_lenght2(t_player_info *player_infos)
{
    find_wall_hit_h_v(player_infos);
    if (player_infos->real_angle == 0  || player_infos->real_angle == M_PI / 2 
        || player_infos->real_angle == (M_PI / 2) * 3 || player_infos->real_angle == M_PI || check_edge(player_infos) == 1)
        return(player_infos->wall_hit->lenght);
    if (player_infos->wall_hit->hit_direction == 0)
    {
       
        if (player_infos->ray_rotation_angle > 0 && player_infos->ray_rotation_angle < M_PI)
        {
            if (player_infos->ray_rotation_angle > M_PI / 2)
                player_infos->ray_rotation_angle = M_PI;
            else
                player_infos->ray_rotation_angle = 0;
            find_wall_hit_h_v(player_infos);
        }
        else
        {
            
            if (player_infos->ray_rotation_angle > (M_PI / 2) * 3)
                player_infos->ray_rotation_angle = 0;
            else
                player_infos->ray_rotation_angle = M_PI;
            find_wall_hit_h_v(player_infos);
        }
    }       
    else
    {
        if (player_infos->ray_rotation_angle > M_PI / 2 && player_infos->ray_rotation_angle < 3 * (M_PI / 2))
        {
            if (player_infos->ray_rotation_angle > M_PI)
                player_infos->ray_rotation_angle = (M_PI / 2) * 3;
            else
                player_infos->ray_rotation_angle = M_PI / 2;
            find_wall_hit_h_v(player_infos);
        }
        else
        {
            if (player_infos->ray_rotation_angle > (M_PI / 2) * 3)
                player_infos->ray_rotation_angle = (M_PI / 2) * 3;
            else
                player_infos->ray_rotation_angle = M_PI / 2;
            find_wall_hit_h_v(player_infos);
        }
    }
    return(player_infos->wall_hit->lenght);

}


void close_doors(t_player_info *player_infos, double lenght)
{
    int y;
    int x;


    
    y = (int)player_infos->j / CUB_SIZE;
    x = (int)player_infos->i / CUB_SIZE;

        if (player_infos->map2[y + 1][x] == 'D')
            player_infos->map[y + 1][x] = '1';
        else if (player_infos->map2[y - 1][x] == 'D' )
            player_infos->map[y - 1][x] = '1';
        else if (player_infos->map2[y][x + 1] == 'D' )
            player_infos->map[y][x + 1] = '1';
        else if (player_infos->map2[y][x - 1] == 'D' )
            player_infos->map[y][x - 1] = '1';
}

void player_new_pos_up(t_player_info *player_infos)
{
    double move_speed;
    double len_to_wall;
    double len_to_wall2;


    move_speed = player_infos->move_speed;
    player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall = get_the_lenght(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall2 = get_the_lenght2(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    close_doors(player_infos, len_to_wall);
    if (len_to_wall2 <= DIS_WALL && player_infos->wall_hit->lenght <= (DIS_WALL) * 2)
        return;
    if (len_to_wall <= DIS_WALL)
    {
        player_infos->new_i = player_infos->i + cos(player_infos->rotation_angle) * move_speed;
        player_infos->new_j = player_infos->j + sin(player_infos->rotation_angle) * move_speed;
        slide_on_the_wall(player_infos);
        return;
    }
    if (len_to_wall - DIS_WALL < player_infos->move_speed)
    {
        
        player_infos->i = player_infos->i + cos(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j + sin(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
           slide_on_the_wall(player_infos);
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
}


void player_new_pos(t_player_info *player_infos)
{
    double move_speed;
    double len_to_wall;
    double len_to_wall2;


    move_speed = player_infos->move_speed;
   player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall = get_the_lenght(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall2 = get_the_lenght2(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    close_doors(player_infos, len_to_wall);
    if (len_to_wall2 <= DIS_WALL && player_infos->wall_hit->lenght <= DIS_WALL * 1.5)
        return;
    if (len_to_wall <= DIS_WALL)
    {

        player_infos->new_i = player_infos->i - cos(player_infos->rotation_angle) * move_speed;
        player_infos->new_j = player_infos->j - sin(player_infos->rotation_angle) * move_speed;
        slide_on_the_wall(player_infos);
        return;
    }
    if (len_to_wall - DIS_WALL < player_infos->move_speed)
    {
        player_infos->i = player_infos->i - cos(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j - sin(player_infos->rotation_angle) * (len_to_wall - DIS_WALL);
        slide_on_the_wall(player_infos);
        
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
}




void player_new_pos_right(t_player_info *player_infos)
{
    double move_speed;
    double len_to_wall;
    double len_to_wall2;


    move_speed = player_infos->move_speed;
   player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall = get_the_lenght(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall2 = get_the_lenght2(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    close_doors(player_infos, len_to_wall);
     if (len_to_wall2 <= DIS_WALL && player_infos->wall_hit->lenght <= DIS_WALL * 1.5)
        return;
    if (len_to_wall <= DIS_WALL)
    {

        player_infos->new_i = player_infos->i + cos(player_infos->rotation_angle + M_PI / 2) * move_speed;
        player_infos->new_j = player_infos->j + sin(player_infos->rotation_angle + M_PI / 2) * move_speed;
         slide_on_the_wall(player_infos);
        return;
    }
    if (len_to_wall - DIS_WALL < player_infos->move_speed)
    {
        player_infos->i = player_infos->i + cos(player_infos->rotation_angle + M_PI / 2) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j + sin(player_infos->rotation_angle + M_PI / 2) * (len_to_wall - DIS_WALL);
         slide_on_the_wall(player_infos);
        
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
}

void player_new_pos_left(t_player_info *player_infos)
{
    double move_speed;
    double len_to_wall;
    double len_to_wall2;


    move_speed = player_infos->move_speed;
   player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall = get_the_lenght(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    len_to_wall2 = get_the_lenght2(player_infos);
    player_infos->ray_rotation_angle = player_infos->real_angle;
    find_wall_hit_h_v(player_infos);
    close_doors(player_infos, len_to_wall);
    if (len_to_wall2 <= DIS_WALL && player_infos->wall_hit->lenght <= DIS_WALL * 1.5)
        return;
    if (len_to_wall <= DIS_WALL)
    {
          player_infos->new_i = player_infos->i + cos(player_infos->rotation_angle - M_PI / 2) * move_speed;
        player_infos->new_j = player_infos->j + sin(player_infos->rotation_angle - M_PI / 2) * move_speed;
         slide_on_the_wall(player_infos);
        return;
    }
    if (len_to_wall - DIS_WALL< player_infos->move_speed)
    {
        player_infos->i = player_infos->i + cos(player_infos->rotation_angle - M_PI / 2) * (len_to_wall - DIS_WALL);
        player_infos->j = player_infos->j + sin(player_infos->rotation_angle - M_PI / 2) * (len_to_wall - DIS_WALL);
         slide_on_the_wall(player_infos);
        
    }
    else if (len_to_wall >= player_infos->move_speed)
    {
        player_infos->j = player_infos->new_j;
        player_infos->i = player_infos->new_i;
    }
}

int check_if_door(t_player_info *player_infos)
{
    int y;
    int x;
    int y2;
    int x2;
    int t = 0;

    if (player_infos->wall_hit->hit_direction == 0)
    {
        if (player_infos->rotation_angle > 0 && player_infos->rotation_angle < M_PI)
            t = 1;
        else
            t = 2;
    }       
    else
    {
        if (player_infos->rotation_angle > M_PI / 2 && player_infos->rotation_angle < 3 * (M_PI / 2))
            t = 3;
        else
            t = 4;
    }

    y = (int)player_infos->j / CUB_SIZE;
    x = (int)player_infos->i / CUB_SIZE;
    y2 = (int)player_infos->new_j / CUB_SIZE;
    x2 = (int)player_infos->new_i / CUB_SIZE;
    if (player_infos->map2[y2][x2] == 'D')
    {
        if (player_infos->map2[y + 1][x] == 'D' && t == 1)
            player_infos->map[y + 1][x] = '0';
        else if (player_infos->map2[y - 1][x] == 'D' && t == 2)
            player_infos->map[y - 1][x] = '0';
        else if (player_infos->map2[y][x - 1] == 'D' && t == 3)
            player_infos->map[y][x - 1] = '0';
        else if (player_infos->map2[y][x + 1] == 'D' && t == 4)
            player_infos->map[y][x + 1] = '0';
        return(0);
    }

    return(1);
    
}

int game_loop(t_base *game)
{
    int i;

    i = 0;


    if (game->s_keys->right)
    {
        game->player_infos->rotation_angle += game->player_infos->rotation_speed;
        game->player_infos->rotation_angle = normalize_angle(game->player_infos->rotation_angle);
        i = 1;
    }
    if (game->s_keys->left)
    {
        game->player_infos->rotation_angle -= game->player_infos->rotation_speed;
        game->player_infos->rotation_angle = normalize_angle(game->player_infos->rotation_angle);
        i = 1;
    }

    // Move forward
    if (game->s_keys->w)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->real_angle = normalize_angle(game->player_infos->rotation_angle);
        player_new_pos_up(game->player_infos);
        i = 1;
    }
    // Move backward
    if (game->s_keys->s)
    {
        game->player_infos->new_i = game->player_infos->i - cos(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j - sin(game->player_infos->rotation_angle) * game->player_infos->move_speed;
        game->player_infos->real_angle = fmod(game->player_infos->rotation_angle * (180 / M_PI) + 180, 360) * (M_PI / 180);
        game->player_infos->real_angle = normalize_angle(game->player_infos->real_angle);
        player_new_pos(game->player_infos);
        i = 1;
    }

    // Move right
    if (game->s_keys->d)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle + M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle + M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->real_angle = fmod(game->player_infos->rotation_angle * (180 / M_PI) + 90, 360) * (M_PI / 180);
        game->player_infos->real_angle = normalize_angle(game->player_infos->real_angle);
        player_new_pos_right(game->player_infos);
        i = 1;
    }

    // Move left
    if (game->s_keys->a)
    {
        game->player_infos->new_i = game->player_infos->i + cos(game->player_infos->rotation_angle - M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->new_j = game->player_infos->j + sin(game->player_infos->rotation_angle - M_PI / 2) * game->player_infos->move_speed;
        game->player_infos->real_angle = fmod(game->player_infos->rotation_angle * (180 / M_PI) + 270, 360) * (M_PI / 180);
        game->player_infos->real_angle = normalize_angle(game->player_infos->real_angle);
        player_new_pos_left(game->player_infos);
        i = 1 ;
    }
    if (game->s_keys->o)
    {
        if (check_if_door(game->player_infos) == 0)
        {
            cast_rays(game);
            draw_minimap(game); // draw minimap 
            mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
        }
    }
    if (i == 1)
    {
            //  draw_map(game);
        //   mlx_clear_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win);
        cast_rays(game);
          draw_minimap(game); // draw minimap 
        mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    }
    return 0;
}



char get_player_pos_and_dir(t_player_info *player_infos)
{
    int i;
    int j;
    char d;

    j = 0;
    while(j < player_infos->map_height)
    {
        i = 0;
        while(i < player_infos->map_width)
        {
            d = player_infos->map[j][i];
            if (d == 'N' || d ==  'S' || d == 'E' || d == 'W')
            {
                player_infos->i = (i + 0.5) * CUB_SIZE;
                player_infos->j = (j + 0.5) * CUB_SIZE;
                return (d);
            }
            i++;
        }
        j++;
    }
}


void init_rotation_angle(char d, t_player_info *player_infos)
{
    if (d == 'N')
        player_infos->rotation_angle = 0 + M_PI / 2;
    else if (d == 'S')
        player_infos->rotation_angle = 0 + 3 * (M_PI / 2);
    else if (d == 'E')
        player_infos->rotation_angle = 0 + M_PI;
    else if (d == 'W')
        player_infos->rotation_angle = 0;
}