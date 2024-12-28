# include "../cub.h"

void find_inters_right(t_player_info *player_infos)
{
    int x, y;
    double  isteps;
    int length;
   
    player_infos->wall_hit->hit_direction = 1;
    isteps = ((int)player_infos->i / CUB_SIZE) * CUB_SIZE + CUB_SIZE;    
    y = ((int)player_infos->j) / CUB_SIZE;
    x = ((int)isteps) / CUB_SIZE;
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] == '1')
    {
        player_infos->wall_hit->ni = isteps;
        player_infos->wall_hit->nj = player_infos->j;
        return;
    }
    while (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] != '1'
        && player_infos->check_one_cub != 1)
    {
        isteps += CUB_SIZE;
        y = ((int)player_infos->j) / CUB_SIZE;
        x = ((int)isteps) / CUB_SIZE;
    }
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->check_one_cub != 1)
    {
        player_infos->wall_hit->ni = isteps;
        player_infos->wall_hit->nj = player_infos->j;
    }
}

void find_inters_down(t_player_info *player_infos)
{
    int x, y;
    double  jsteps;
    int length;
   
    jsteps = ((int)player_infos->j / CUB_SIZE) * CUB_SIZE + CUB_SIZE;    
    x = ((int)player_infos->i) / CUB_SIZE;
    y = ((int)jsteps) / CUB_SIZE;
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] == '1')
    {
        player_infos->wall_hit->nj = jsteps;
        player_infos->wall_hit->ni = player_infos->i;
        return;
    }
    while (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] != '1'
        && player_infos->check_one_cub != 1)
    {
        jsteps += CUB_SIZE;
        x = ((int)player_infos->i) / CUB_SIZE;
        y = ((int)jsteps) / CUB_SIZE;
    }
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->check_one_cub != 1)
    {
        player_infos->wall_hit->nj = jsteps;
        player_infos->wall_hit->ni = player_infos->i;
    }


}

void find_inters_left(t_player_info *player_infos)
{
    int x, y;
    double  isteps;
    int length;
   
   player_infos->wall_hit->hit_direction = 1;
    isteps = ((int)player_infos->i / CUB_SIZE) * CUB_SIZE;    
    y = ((int)player_infos->j) / CUB_SIZE;
    x = ((int)isteps - 1) / CUB_SIZE;
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] == '1')
    {
        player_infos->wall_hit->ni = isteps;
        player_infos->wall_hit->nj = player_infos->j;
        return;
    }
    while (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] != '1'
        && player_infos->check_one_cub != 1)
    {
        isteps -= CUB_SIZE;
        y = ((int)player_infos->j) / CUB_SIZE;
        x = ((int)isteps - 1) / CUB_SIZE;
    }
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->check_one_cub != 1)
    {
        player_infos->wall_hit->ni = isteps;
        player_infos->wall_hit->nj = player_infos->j;
    }
    

}

void find_inters_up(t_player_info *player_infos)
{
    int x, y;
    double  jsteps;
    int length;
   
    jsteps = ((int)player_infos->j / CUB_SIZE) * CUB_SIZE;
    x = ((int)player_infos->i) / CUB_SIZE;
    y = ((int)jsteps - 1) / CUB_SIZE;
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] == '1')
    {
        player_infos->wall_hit->nj = jsteps;
        player_infos->wall_hit->ni = player_infos->i;
        return;
    }
    while (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->map[y][x] != '1'
        && player_infos->check_one_cub != 1)
    {
        jsteps -= CUB_SIZE;
        x = ((int)player_infos->i) / CUB_SIZE;
        y = ((int)jsteps -1) / CUB_SIZE;
    }
    if (y >= 0 && y < player_infos->map_height && x >= 0 && x < player_infos->map_width && player_infos->check_one_cub != 1)
    {
        player_infos->wall_hit->nj = jsteps;
        player_infos->wall_hit->ni = player_infos->i;
    }

}