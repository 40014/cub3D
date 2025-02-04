# include "../cub.h"


double calculate_wall_x(t_player_info *ray)
{
    double wall_x;

    if (ray->wall_hit->hit_direction == 0)
        wall_x = fmod(ray->wall_hit->ni, CUB_SIZE);
    else
        wall_x = fmod(ray->wall_hit->nj, CUB_SIZE);
    return (wall_x);
}

int get_texture_index(t_player_info *player_infos, int n)
{
    int x;
    int y;

    if (player_infos->wall_hit->hit_direction == 0)
    {
        if (player_infos->ray_rotation_angle >= 0 && player_infos->ray_rotation_angle < M_PI)
            n = 0;
        else
            n = 1;
    }
    else
    {
        if (player_infos->ray_rotation_angle >= M_PI / 2 && player_infos->ray_rotation_angle < 3 * (M_PI / 2))
            n = 2;
        else
            n = 3;
    }
    get_the_real_hit_point(player_infos);
    y = (int)player_infos->wall_hit->nj / CUB_SIZE;
    x = (int)player_infos->wall_hit->ni / CUB_SIZE;
    if (player_infos->map2[y][x] == 'D')
        return (4);
    return (n);
}

int get_texture_x(t_base *game, double wall_x, int n)
{
    int tex_x;
    t_texture *texture;

    texture = game->textures[n];
    tex_x = (int)(wall_x * ((double)texture->width / TILE_SIZE));
    if (tex_x < 0)
        tex_x = 0;
    return (tex_x);
}

double get_wall_height(t_player_info *player_infos, double distance_projection)
{
    double correct_lenght;
    double wall_height;

    player_infos->ray_rotation_angle = normalize_angle(player_infos->ray_rotation_angle);
    casting_rays(player_infos);
    correct_lenght = player_infos->wall_hit->lenght * cos(player_infos->ray_rotation_angle - player_infos->rotation_angle);
    wall_height = (CUB_SIZE / correct_lenght) * distance_projection;
    return (wall_height);

}
