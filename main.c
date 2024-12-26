# include "cub.h"




int main(int ac, char **av)
{
    t_mlx_ptrs mlx_ptrs;
    t_player_info player_infos;
    t_base game;

    if (ac != 2)
        return (1);
    //parsing
    ft_init_struct_game(&game);
    parsing(&game, av[1]);
    mlx_ptrs.mlx_ptr = mlx_init();
    mlx_ptrs.win = mlx_new_window(mlx_ptrs.mlx_ptr, game.map_width * CUB_SIZE, game.map_height * CUB_SIZE, "Cub3D");
    mlx_ptrs.img = mlx_new_image(mlx_ptrs.mlx_ptr, game.map_width * CUB_SIZE, game.map_height * CUB_SIZE);
    mlx_ptrs.addr = mlx_get_data_addr(mlx_ptrs.img, &mlx_ptrs.bpp, &mlx_ptrs.line_length, &mlx_ptrs.endian);
    initialize_keys(&game);
    // draw map
    game.mlx_ptrs = &mlx_ptrs;
    mlx_hook(mlx_ptrs.win, 2, 1L << 0, key_press, &game);
    mlx_hook(mlx_ptrs.win, 3, 1L << 1, key_release, &game);
    draw_map(&game);
    // init_player_infos
    player_infos.map = game.map;
    player_infos.map_width = game.map_width;
    player_infos.map_height = game.map_height;
    player_infos.rotation_angle = (M_PI / 180) * 0;
    player_infos.rotation_speed = 3 * (M_PI / 180);
    player_infos.move_speed = 15;
    game.player_infos = &player_infos;
    get_player_pos(&player_infos);
    mlx_put_image_to_window(mlx_ptrs.mlx_ptr, mlx_ptrs.win, mlx_ptrs.img, 0, 0);
    mlx_loop_hook(game.mlx_ptrs->mlx_ptr, game_loop, &game);
    mlx_loop(mlx_ptrs.mlx_ptr);
    return(0);
}