# include "cub.h"


void load_texture(t_base *game, t_texture *texture, char *path)
{
    texture->img_ptr = mlx_xpm_file_to_image(game->mlx_ptrs->mlx_ptr, path, &texture->width, &texture->height);
    if (!texture->img_ptr)
    {
        ft_printf_err("Error\nFailed to load texture:\n");
        exit(1);
    }
    texture->data = mlx_get_data_addr(texture->img_ptr, &texture->bpp, &texture->line_length, &texture->endian);
    if (!texture->data)
    {
        ft_printf_err("Error\nFailed to get texture data for: \n");
        exit(1);
    }
}

void load_all_textures(t_base *game)
{
    int     i;

    i = 0;
    while (i < 5)
    {
        if (game->textures[i] != NULL && game->path[i] != NULL)
            load_texture(game, game->textures[i], game->path[i]);
        i++;
    }
}

int handle_mouse_move(int x, int y, t_base *game)
{
    static int last_x = SCREEN_SIZE / 2;
    int     delta_x;

    delta_x = x - last_x;
    game->player_infos->rotation_angle = delta_x * MOUSE_SPED;
    game->player_infos->rotation_angle = normalize_angle(game->player_infos->rotation_angle);
    cast_rays(game);
    draw_minimap(game);
    draw_weapon_sprite(game);
    mlx_put_image_to_window(game->mlx_ptrs->mlx_ptr, game->mlx_ptrs->win, game->mlx_ptrs->img, 0, 0);
    return (0);
}

void change_map_and_dup(t_base *game)
{
    int j;
    int i;

    j = 0;
    game->player_infos->map2 = malloc(sizeof(char*) * game->map_height);
    while(j < game->map_height)
    {
        i = 0;
        game->player_infos->map2[j] = ft_strdup(game->map[j]);
        while(i < game->map_width)
        {
            if (game->map[j][i] == 'D')
                game->map[j][i] = '1';
            i++;
        }
        j++;
    }
}

void init_player_infos(t_player_info *player_infos, t_base *game, t_wall_hit *wall_hit)
{
    player_infos->wall_hit = wall_hit;
    player_infos->map = game->map;
    player_infos->map_width = game->map_width;
    player_infos->map_height = game->map_height;
    player_infos->rotation_speed = R_SPEED * (M_PI / 180);
    player_infos->move_speed = P_SPEED;
}


void initialize_game(t_base *game)
{
    t_mlx_ptrs      mlx_ptrs;
    t_player_info   player_infos;
    t_wall_hit  wall_hit;
    
    mlx_ptrs.mlx_ptr = mlx_init();
    game->mlx_ptrs = &mlx_ptrs;
    mlx_ptrs.win = mlx_new_window(mlx_ptrs.mlx_ptr, SCREEN_SIZE, SCREEN_HEIGHT, "Cub3D");
    mlx_ptrs.img = mlx_new_image(mlx_ptrs.mlx_ptr, SCREEN_SIZE, SCREEN_HEIGHT);
    mlx_ptrs.addr = mlx_get_data_addr(mlx_ptrs.img, &mlx_ptrs.bpp, &mlx_ptrs.line_length, &mlx_ptrs.endian);
    load_all_textures(game);
    init_weapon_sprite(game);
    initialize_keys(game);
    init_player_infos(&player_infos, game, &wall_hit);
    game->player_infos = &player_infos;
    change_map_and_dup(game);
    init_rotation_angle(get_player_pos_and_dir(&player_infos), &player_infos);
    cast_rays(game);
    draw_minimap(game);
    draw_weapon_sprite(game);
    mlx_put_image_to_window(mlx_ptrs.mlx_ptr, mlx_ptrs.win, mlx_ptrs.img, 0, 0);
    mlx_hook(mlx_ptrs.win, 2, 1L << 0, key_press, game);
    mlx_hook(mlx_ptrs.win, 3, 1L << 1, key_release, game);
    mlx_hook(mlx_ptrs.win, 4, 1L << 2, mouse_press, game);
    mlx_hook(mlx_ptrs.win, 5, 1L << 3, mouse_release, game);
    mlx_hook(mlx_ptrs.win, 17, 0L, exit_game, game);
    // mlx_hook(mlx_ptrs.win, 6, 1L << 6, handle_mouse_move, &game);
    mlx_loop_hook(game->mlx_ptrs->mlx_ptr, game_loop, game);
    mlx_loop(mlx_ptrs.mlx_ptr);
}

int main(int ac, char **av)
{
    t_base game;

    if (ac != 2)
        return (1);
    ft_init_struct_game(&game);
    parsing(&game, av[1]);
    initialize_game(&game);
    return(0);
}