# include "../cub.h"

double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}
void calculate_length(t_player_info *player_infos, double x, double y)
{
    player_infos->wall_hit->lenght = sqrt(pow(x - player_infos->i, 2) + pow(y - player_infos->j, 2));
}

void get_the_real_hit_point(t_player_info *player_infos)
{
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
}

int out_map(t_player_info *player_infos, int x, int y)
{
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width)
        return(0);
    return (1); 
}

void apply_values(t_player_info *player_infos, double jsteps, double isteps, char c)
{
    if (c == 'h')
    {
        player_infos->wall_hit->hi = isteps;
        player_infos->wall_hit->hj = jsteps;
    }
    else
    {
        player_infos->wall_hit->vi = isteps;
        player_infos->wall_hit->vj = jsteps;
    }
}