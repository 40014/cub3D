# include "cub.h"




int main(int ac, char **av)
{
    t_mlx_ptrs mlx_ptrs;
    t_player_info player_infos;
    t_base game;
    t_wall_hit wall_hit;

    if (ac != 2)
        return (1);
    //parsing
    ft_init_struct_game(&game);
    parsing(&game, av[1]);
    mlx_ptrs.mlx_ptr = mlx_init();
    mlx_ptrs.win = mlx_new_window(mlx_ptrs.mlx_ptr, SCREEN_SIZE, SCREEN_HEIGHT, "Cub3D");
    mlx_ptrs.img = mlx_new_image(mlx_ptrs.mlx_ptr, SCREEN_SIZE, SCREEN_HEIGHT);
    mlx_ptrs.addr = mlx_get_data_addr(mlx_ptrs.img, &mlx_ptrs.bpp, &mlx_ptrs.line_length, &mlx_ptrs.endian);
    initialize_keys(&game);
    // draw map
    game.mlx_ptrs = &mlx_ptrs;
    mlx_hook(mlx_ptrs.win, 2, 1L << 0, key_press, &game);
    mlx_hook(mlx_ptrs.win, 3, 1L << 1, key_release, &game);
    //draw_map(&game);
    // init_player_infos
    player_infos.wall_hit = &wall_hit;
    player_infos.check_one_cub = 0;
    player_infos.map = game.map;
    player_infos.map_width = game.map_width;
    player_infos.map_height = game.map_height;
    player_infos.rotation_speed = R_SPEED * (M_PI / 180);
    player_infos.move_speed = P_SPEED;
    game.player_infos = &player_infos;
    init_rotation_angle(get_player_pos_and_dir(&player_infos), &player_infos);

    cast_rays(&game);
    mlx_put_image_to_window(mlx_ptrs.mlx_ptr, mlx_ptrs.win, mlx_ptrs.img, 0, 0);
    mlx_loop_hook(game.mlx_ptrs->mlx_ptr, game_loop, &game);
    mlx_loop(mlx_ptrs.mlx_ptr);
    return(0);
}