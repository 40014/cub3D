#include "../cub3D_bonus.h"

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

char get_player_pos_and_dir(t_player_info *player_infos)
{
    int i;
    int j;
    char d;

    j = 0;
    while (j < player_infos->map_height)
    {
        i = 0;
        while (i < player_infos->map_width)
        {
            d = player_infos->map[j][i];
            if (d == 'N' || d == 'S' || d == 'E' || d == 'W')
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

int angle_direction(t_player_info *player_infos)
{
    if (player_infos->wall_hit->hit_direction == 0)
    {
        if (player_infos->rotation_angle > 0 && player_infos->rotation_angle < M_PI)
            return(1);
        else
            return(2);
    }
    else
    {
        if (player_infos->rotation_angle > M_PI / 2 && player_infos->rotation_angle < 3 * (M_PI / 2))
            return(3);
        else
           return(4);
    }
    return(0);
}

int ray_angle_direction(t_player_info *player_infos)
{
    if (player_infos->wall_hit->hit_direction == 0)
    {
        if (player_infos->ray_rotation_angle > 0 && player_infos->ray_rotation_angle < M_PI)
            return(1);
        else
            return(2);
    }
    else
    {
        if (player_infos->ray_rotation_angle > M_PI / 2 && player_infos->ray_rotation_angle < 3 * (M_PI / 2))
            return(3);
        else
           return(4);
    }
    return(0);
}

void close_doors(t_player_info *player_infos)
{
    int y;
    int x;

    y = (int)player_infos->j / CUB_SIZE;
    x = (int)player_infos->i / CUB_SIZE;
    if (y + 2 < player_infos->map_height && player_infos->map2[y + 2][x] == 'D')
        player_infos->map[y + 2][x] = '1';
    else if (y - 2 >= 0 && player_infos->map2[y - 2][x] == 'D')
        player_infos->map[y - 2][x] = '1';
    else if (x + 2 < player_infos->map_width && player_infos->map2[y][x + 2] == 'D')
        player_infos->map[y][x + 2] = '1';
    else if (x - 2 >= 0 && player_infos->map2[y][x - 2] == 'D')
        player_infos->map[y][x - 2] = '1';
    else if (player_infos->map2[y + 1][x - 1] == 'D')
        player_infos->map[y + 1][x - 1] = '1';
    else if (player_infos->map2[y + 1][x + 1] == 'D')
        player_infos->map[y + 1][x + 1] = '1';
    else if (player_infos->map2[y - 1][x + 1] == 'D')
        player_infos->map[y - 1][x + 1] = '1';
    else if (player_infos->map2[y - 1][x - 1] == 'D')
        player_infos->map[y - 1][x - 1] = '1';
}


void update_angle(t_player_info *player_infos, int sign, double angle)
{
    if (sign == 1)
    {
        angle += player_infos->rotation_angle;
        player_infos->rotation_angle = normalize_angle(angle);
    }
    else
    {
        angle = player_infos->rotation_angle - angle;
        player_infos->rotation_angle = normalize_angle(angle);
    }
}