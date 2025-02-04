# include "../cub.h"

void find_inters_up_left_h(t_player_info *player_infos, int y, int x)
{
    double  isteps;
    double  jsteps;

    jsteps = ((int)player_infos->j / CUB_SIZE) * CUB_SIZE;    
    isteps = player_infos->i - (player_infos->j - jsteps) / fabs(tan(player_infos->ray_rotation_angle));
    y = ((int)jsteps - 1) / CUB_SIZE;
    x = ((int)isteps ) / CUB_SIZE;
    if (((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
        || check_the_edge1(player_infos, jsteps, isteps) == 1)
    {
        player_infos->wall_hit->hi = isteps;
        player_infos->wall_hit->hj = jsteps;
        return;
    }
    while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1'
        && check_the_edge1(player_infos, jsteps, isteps) != 1 )
    {
        jsteps -= CUB_SIZE;
        isteps -= CUB_SIZE / fabs(tan(player_infos->ray_rotation_angle));
        y = ((int)jsteps - 1) / CUB_SIZE;
        x = ((int)isteps ) / CUB_SIZE;
    }
    if (out_map(player_infos, x, y) == 0)
        apply_values(player_infos, jsteps, isteps, 'h');
}


void find_inters_up_left_v(t_player_info *player_infos, int y, int x)
{
    double  isteps;
    double  jsteps;

    isteps = ((int)player_infos->i / CUB_SIZE) * CUB_SIZE;
    jsteps = player_infos->j - (player_infos->i - isteps) * fabs(tan(player_infos->ray_rotation_angle));
    y = ((int)jsteps ) / CUB_SIZE;
    x = ((int)isteps - 1) / CUB_SIZE;
    if (((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] == '1')
        || check_the_edge1(player_infos, jsteps, isteps) == 1)
    {
        player_infos->wall_hit->vi = isteps;
        player_infos->wall_hit->vj = jsteps;
        return;
    }
    while ((out_map(player_infos, x, y) == 0) && player_infos->map[y][x] != '1'
        && check_the_edge1(player_infos, jsteps, isteps) != 1 )
    {
        isteps -= CUB_SIZE;
        jsteps -= CUB_SIZE * fabs(tan(player_infos->ray_rotation_angle));
        y = ((int)jsteps ) / CUB_SIZE;
        x = ((int)isteps - 1) / CUB_SIZE;
    }
    if (out_map(player_infos, x, y) == 0)
        apply_values(player_infos, jsteps, isteps, 'v');
}

void find_nearest_wall_hit_up_left(t_player_info *player_infos)
{
    if (player_infos->wall_hit->hi == -1 || player_infos->wall_hit->hj == -1)
    {
        player_infos->wall_hit->nj = player_infos->wall_hit->vj;
        player_infos->wall_hit->ni = player_infos->wall_hit->vi;
        player_infos->wall_hit->hit_direction = 1;
    }
    else if (player_infos->wall_hit->vi == -1 || player_infos->wall_hit->vj == -1)
    {
        player_infos->wall_hit->nj = player_infos->wall_hit->hj;
        player_infos->wall_hit->ni = player_infos->wall_hit->hi;
    }
    else if (player_infos->wall_hit->hj > player_infos->wall_hit->vj &&
        player_infos->wall_hit->hi > player_infos->wall_hit->vi)
    {
        player_infos->wall_hit->nj = player_infos->wall_hit->hj;
        player_infos->wall_hit->ni = player_infos->wall_hit->hi;
    }
    else
    {
        player_infos->wall_hit->nj = player_infos->wall_hit->vj;
        player_infos->wall_hit->ni = player_infos->wall_hit->vi;
        player_infos->wall_hit->hit_direction = 1;
    }
    calculate_length(player_infos, player_infos->wall_hit->ni, player_infos->wall_hit->nj);
}
