# include "../cub.h"




void find_inters_up_left_h(t_player_info *player_infos)
{
    int x, y;
    double jsteps, isteps;
    int length;

    player_infos->wall_hit->hi = -1;
    player_infos->wall_hit->hj = -1;
    jsteps = ((int)player_infos->j / CUB_SIZE) * CUB_SIZE;    
    isteps = player_infos->i - (player_infos->j - jsteps) / fabs(tan(player_infos->ray_rotation_angle));
    y = ((int)jsteps - 1) / CUB_SIZE;
    x = ((int)isteps - 1) / CUB_SIZE;
    if ((y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] == '1')
        || check_the_edge1(player_infos, jsteps, isteps) == 1)
    {
       // printf("yeah j : %lf      i : %lf\n", jsteps, isteps);
        player_infos->wall_hit->hi = isteps;
        player_infos->wall_hit->hj = jsteps;
        return;
    }
    while (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] != '1'
        && check_the_edge1(player_infos, jsteps, isteps) != 1 && player_infos->check_one_cub != 1)
    {
        jsteps -= CUB_SIZE;
        isteps -= CUB_SIZE / fabs(tan(player_infos->ray_rotation_angle));
        y = ((int)jsteps - 1) / CUB_SIZE;
        x = ((int)isteps - 1) / CUB_SIZE;

    }
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->check_one_cub != 1)
    {
        player_infos->wall_hit->hi = isteps;
        player_infos->wall_hit->hj = jsteps;
    }
}


void find_inters_up_left_v(t_player_info *player_infos)
{
    int x, y;
    double jsteps, isteps;

    player_infos->wall_hit->vi = -1;
    player_infos->wall_hit->vj = -1;
    isteps = ((int)player_infos->i / CUB_SIZE) * CUB_SIZE;
    jsteps = player_infos->j - (player_infos->i - isteps) * fabs(tan(player_infos->ray_rotation_angle));
    y = ((int)jsteps - 1) / CUB_SIZE;
    x = ((int)isteps - 1) / CUB_SIZE;
    if ((y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] == '1')
        || check_the_edge1(player_infos, jsteps, isteps) == 1)
    {
        player_infos->wall_hit->vi = isteps;
        player_infos->wall_hit->vj = jsteps;
        return;
    }

    while (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] != '1'
        && check_the_edge1(player_infos, jsteps, isteps) != 1 && player_infos->check_one_cub != 1)
    {
        isteps -= CUB_SIZE;
        jsteps -= CUB_SIZE * fabs(tan(player_infos->ray_rotation_angle));
        y = ((int)jsteps - 1) / CUB_SIZE;
        x = ((int)isteps - 1) / CUB_SIZE;
    }
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->check_one_cub != 1)
    {
        player_infos->wall_hit->vi = isteps;
        player_infos->wall_hit->vj = jsteps;
    }
}

void find_nearest_wall_hit_up_left(t_player_info *player_infos)
{
  //  printf("hj : %lf     hi : %lf ********   vj : %lf   vi : %lf\n", player_infos->wall_hit->hj, player_infos->wall_hit->hi, player_infos->wall_hit->vj, player_infos->wall_hit->vi);
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
}