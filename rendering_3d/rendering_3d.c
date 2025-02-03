# include "../cub.h"


void draw_wall_line(t_base *game, double line_length, double x, int tex_x, int n)
{
    double y;
    double start_wall;
    double end_wall;
    double i;
    int tex_y;
    int color;
    double texture_step;
    double texture_pos;
    t_texture *texture;

    start_wall = (SCREEN_HEIGHT / 2) - (line_length / 2);
    end_wall = start_wall + line_length;
    if (start_wall < 0)
        start_wall = 0;
    if (end_wall > SCREEN_HEIGHT)
        end_wall = SCREEN_HEIGHT;
    y = start_wall;
    i = 0;
    texture = game->textures[n];
    while (i < start_wall)
    {
        my_mlx_pixel_put(game, x, i, game->ceiling_color);
        i++;
    }
    texture_step = (double)texture->height / line_length;
    texture_pos = (start_wall - ((SCREEN_HEIGHT / 2) - (line_length / 2))) * texture_step;
    while (y < end_wall)
    {
        tex_y = (int)texture_pos;
        if (tex_y >= texture->height)
            tex_y = texture->height - 1;
        color = *(unsigned int *)((char *)texture->data + (tex_y * texture->line_length + tex_x * (texture->bpp / 8)));
        my_mlx_pixel_put(game, x, y, color);
        texture_pos += texture_step;
        y++;
    }

    i = end_wall;
    while (i < SCREEN_HEIGHT)
    {
        my_mlx_pixel_put(game, x, i, game->floor_color);
        i++;
    }
}

void rendering_3d(t_base *game)
{
    double  start_angle;
    double  increment;
    double  distance_projection;
    double  wall_height;
    int     colome;
    double  wall_x;
    int     tex_x;
    int     n;

    start_angle = game->player_infos->rotation_angle - (FOV / 2) * (M_PI / 180);
    game->player_infos->ray_rotation_angle = start_angle;
    distance_projection = (SCREEN_SIZE / 2) / (tan((FOV / 2) * (M_PI / 180)));
    increment = FOV * (M_PI / 180) / SCREEN_SIZE;
    colome = 0;
    while (colome < SCREEN_SIZE)
    {
        wall_height = get_wall_height(game->player_infos, distance_projection);
        wall_x = calculate_wall_x(game->player_infos);
        n = get_texture_index(game->player_infos, n);
        tex_x = get_texture_x(game, wall_x, n);
        draw_wall_line(game, wall_height, colome, tex_x, n);
        game->player_infos->ray_rotation_angle += increment;
        colome++;
    }
}
