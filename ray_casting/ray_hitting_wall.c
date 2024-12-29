# include "../cub.h"




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

int check_straight_ray(t_player_info *player_infos, int angle_of_ray)
{
    
    if (angle_of_ray == 0)
    {
        find_inters_right(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->j);
        return(1);
    }
    else if(angle_of_ray == 90)
    {
        find_inters_down(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->i, player_infos->wall_hit->nj);
        return(1);
    }
    else if (angle_of_ray == 180)
    {
        find_inters_left(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->j);
        return(1);
    }
    else if (angle_of_ray == 270)
    {
        find_inters_up(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->i, player_infos->wall_hit->nj);
        return(1);
    }
    return(0);
}

int find_wall_hit_h_v(t_player_info *player_infos)
{
    int angle_of_ray;
    int lenght;

    angle_of_ray = player_infos->ray_rotation_angle * 180/M_PI;
    if (check_straight_ray(player_infos, angle_of_ray) == 1)
        return 1;
    if (angle_of_ray > 0 && angle_of_ray < 90)
    {
        find_inters_down_right_h(player_infos);
        find_inters_down_right_v(player_infos);
        find_nearest_wall_hit_down_right(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
    }
    else if (angle_of_ray > 90 && angle_of_ray < 180)
    {
        find_inters_down_left_h(player_infos);
        find_inters_down_left_v(player_infos);
        find_nearest_wall_hit_down_left(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
    }
    else if (angle_of_ray > 180 && angle_of_ray < 270)
    {
        find_inters_up_left_h(player_infos);
        find_inters_up_left_v(player_infos);
        find_nearest_wall_hit_up_left(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);

    }
    else if (angle_of_ray > 270 && angle_of_ray < 360)
    {
        
        find_inters_up_right_h(player_infos);
        find_inters_up_right_v(player_infos);
        find_nearest_wall_hit_up_right(player_infos);
        player_infos->wall_hit->lenght = calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
    }
    return (0);
}



void cast_rays(t_base *game)
{
    double start_angle_of_ray;
    double end_angle_of_ray;
    double angle_of_ray;
    int normal_angle;


    game->player_infos->map = game->map;
    game->player_infos->map_width = game->map_width;
    game->player_infos->map_height = game->map_height;
   // game->player_infos->ray_rotation_angle = game->player_infos->rotation_angle;
    start_angle_of_ray = (game->player_infos->rotation_angle * 180/M_PI) - FOV/2;
    end_angle_of_ray = (game->player_infos->rotation_angle * 180/M_PI) + FOV/2;
    angle_of_ray = start_angle_of_ray;
    int count = 1;
    double ngl = (double)(FOV * (M_PI / 180) / (double)(game->map_width * CUB_SIZE));
    while (angle_of_ray <= end_angle_of_ray)  
    {
        game->player_infos->wall_hit->hit_direction = 0;
        normal_angle = ((int)angle_of_ray + 360) % 360;
        game->player_infos->ray_rotation_angle = normal_angle * (M_PI / 180);
        find_wall_hit_h_v(game->player_infos);
            draw_line2(game, game->player_infos->wall_hit->lenght, 0xff0000);
        angle_of_ray++;
    }
   

}