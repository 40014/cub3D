# include "../cub.h"




void draw_wall_line(t_base *game, double line_length, double x, int color)
{
    double y;
    double start_wall;
    double end_wall;
    double i;

    start_wall = (SCREEN_HEIGHT / 2) - (line_length / 2);
    end_wall = start_wall + line_length;
    y = start_wall;
    i = 0;
    while(i < start_wall)
    {
        my_mlx_pixel_put(game, x, i, 0x000000);
        i++;
    }
    while (y < end_wall)
    {
        my_mlx_pixel_put(game, x, y, color);
        y++;
    }
    i = end_wall++;
    while(i < SCREEN_HEIGHT)
    {
        my_mlx_pixel_put(game, x, i, 0x70442C);
        i++;
    }  
}

void draw_line2(t_base *game, double line_lenght, int color)
{
    double x1;
    double y1;
    int x;
    int y;

    while(line_lenght >= 0)
    {
        x1 = game->player_infos->i + cos(game->player_infos->ray_rotation_angle) * line_lenght;
        y1 = game->player_infos->j + sin(game->player_infos->ray_rotation_angle) * line_lenght;
        y = (int)y1 / CUB_SIZE;
        x = (int)x1 / CUB_SIZE;
        my_mlx_pixel_put(game, x1, y1, color);
        line_lenght--;
    }
   
}

double calculate_length(t_player_info *player_infos, double x, double y)
{
    return sqrt(pow(x - player_infos->i, 2) + pow(y - player_infos->j, 2));
}

int check_straight_ray(t_player_info *player_infos, double angle_of_ray)
{
    
    if (angle_of_ray == 0)
    {
        find_inters_right(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->j);
        return(1);
    }
    else if(angle_of_ray == M_PI / 2)
    {
        find_inters_down(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->i, player_infos->wall_hit->nj);
        return(1);
    }
    else if (angle_of_ray == M_PI)
    {
        find_inters_left(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->j);
        return(1);
    }
    else if (angle_of_ray == 3 * M_PI / 2)
    {
        find_inters_up(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->i, player_infos->wall_hit->nj);
        return(1);
    }
    return(0);
}

int find_wall_hit_h_v(t_player_info *player_infos)
{
    double angle_of_ray;
    int lenght;
     int count = player_infos->colome;


    angle_of_ray = player_infos->ray_rotation_angle;
    if (check_straight_ray(player_infos, angle_of_ray) == 1)
        return 1;
    if (angle_of_ray > 0 && angle_of_ray < M_PI / 2)
    {  
        find_inters_down_right_h(player_infos);
        find_inters_down_right_v(player_infos);
        find_nearest_wall_hit_down_right(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
    }
    else if (angle_of_ray > M_PI / 2 && angle_of_ray < M_PI)
    {
        find_inters_down_left_h(player_infos);
        find_inters_down_left_v(player_infos);
        find_nearest_wall_hit_down_left(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
    }
     else if (angle_of_ray > M_PI && angle_of_ray < 3 * M_PI / 2)
    {
        find_inters_up_left_h(player_infos);
        find_inters_up_left_v(player_infos);
        find_nearest_wall_hit_up_left(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
    }
     else if (angle_of_ray > 3 * M_PI / 2 && angle_of_ray < 2 * M_PI)
    {
        
        find_inters_up_right_h(player_infos);
        find_inters_up_right_v(player_infos);
        find_nearest_wall_hit_up_right(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
    }
    return (0);
}



double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}




void cast_rays(t_base *game)
{
    double start_angle_of_ray;
    double end_angle_of_ray;
    double increment;
    double distance_projection;
    double wall_height;
    double correct_lenght;
    int colome;
    int x;
    int y;

    game->player_infos->map = game->map;
    game->player_infos->map_width = game->map_width;
    game->player_infos->map_height = game->map_height;

    start_angle_of_ray = game->player_infos->rotation_angle - (FOV / 2) * (M_PI / 180);
    end_angle_of_ray = game->player_infos->rotation_angle + (FOV / 2) * (M_PI / 180);
    colome = 0;
    game->player_infos->ray_rotation_angle = start_angle_of_ray;

    distance_projection = (SCREEN_SIZE / 2) / (tan((FOV / 2) * (M_PI / 180)));
    increment = FOV * (M_PI / 180) /SCREEN_SIZE;
   
    while (colome < SCREEN_SIZE)
    {
        
         game->player_infos->wall_hit->hit_direction = 0;
        game->player_infos->ray_rotation_angle = normalize_angle(game->player_infos->ray_rotation_angle);
        game->player_infos->colome = colome;
        find_wall_hit_h_v(game->player_infos);
        correct_lenght = game->player_infos->wall_hit->lenght * cos(game->player_infos->ray_rotation_angle - game->player_infos->rotation_angle );
        wall_height = (CUB_SIZE / correct_lenght) * distance_projection;
        if (wall_height > SCREEN_HEIGHT)
            wall_height = SCREEN_HEIGHT;
        if (game->player_infos->wall_hit->hit_direction == 1)
            draw_wall_line(game, wall_height, colome, 0xC0C0C0);
        else
           draw_wall_line(game, wall_height, colome, 0xffffff);
        //  draw_line2(game, game->player_infos->wall_hit->lenght, 0xfff0000);
        game->player_infos->ray_rotation_angle += increment;
        colome++;
        
    }

    mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
   
}



