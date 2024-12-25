#include "cub3D.h"

#define TILE_SIZE 32

#define W_KEY        119
#define S_KEY        115
#define A_KEY        97
#define D_KEY        100
#define LEFT_ARROW   65361
#define RIGHT_ARROW  65363
#define ESC          65307



void ft_init_struct_game(t_base *game)
{
    int i;

    i = 0;
    game->fd = -1;
    game->map = NULL;
    game->map_height = 0;
    game->map_width = 0;
    game->player_dir = 0;
    game->player_x = -1;
    game->player_y = -1;
    game->floor_color = -1;
    game->ceiling_color = -1;
    while (i < 4)
    {
        game->textures[i] = NULL;
        i++;
    }
}

int key_press(int keycode, t_base *game)
{
    if (keycode == ESC)
        exit(0);
    if (keycode == W_KEY)
        game->s_keys->w = 1;
    else if (keycode == A_KEY)
        game->s_keys->a = 1;
    else if (keycode == S_KEY)
        game->s_keys->s = 1;
    else if (keycode == D_KEY)
        game->s_keys->d = 1;
    else if (keycode == LEFT_ARROW)
        game->s_keys->left = 1;
    else if (keycode == RIGHT_ARROW)
        game->s_keys->right = 1;
    return (0);
}

int key_release(int keycode, t_base *game)
{
    if (keycode == W_KEY)
        game->s_keys->w = 0;
    else if (keycode == A_KEY)
        game->s_keys->a = 0;
    else if (keycode == S_KEY)
        game->s_keys->s = 0;
    else if (keycode == D_KEY)
        game->s_keys->d = 0;
    else if (keycode == LEFT_ARROW)
        game->s_keys->left = 0;
    else if (keycode == RIGHT_ARROW)
        game->s_keys->right = 0;
    return (0);
}

void initialize_keys(t_base *game)
{
    game->s_keys = malloc(sizeof(t_keys));
    if (!game->s_keys)
    {
        perror("Error allocating memory for keys");
        exit(1);
    }

    game->s_keys->w = 0;
    game->s_keys->s = 0;
    game->s_keys->a = 0;
    game->s_keys->d = 0;
    game->s_keys->left = 0;
    game->s_keys->right = 0;
}



void my_mlx_pixel_put(t_base *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= game->map_width * TILE_SIZE || y < 0 || y >= game->map_height * TILE_SIZE)
        return ;
    dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
    
    *(unsigned int *)dst = color;
}

void draw_square(t_base *game, int x, int y, int color)
{
    int i, j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            my_mlx_pixel_put(game, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_base *game)
{
    int i;
    int j;
    int y;
    int x;

    y = 0;
    i = 0;
    while (game->map[i])
    {
        x = 0;
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '1')
                draw_square(game, x, y, 0x0033FF33);
            else if (game->map[i][j] == '0')
                draw_square(game, x, y, 0xFFFFFF);
            else if (game->map[i][j] == ' ')
                draw_square(game, x, y, 0x00CC6633);
            else if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
                     game->map[i][j] == 'E' || game->map[i][j] == 'W')
                draw_square(game, x, y, 0xFF0000);
            j++;
            x = x + TILE_SIZE; // Move to the next tile position horizontally
        }
        i++;
        y = y + TILE_SIZE; // Move to the next tile position vertically
    
    }
}
 

int main(int ac, char **av)
{
    t_base game;
    int i;

    i = 0;
    if (ac != 2)
        return (1);
    ft_init_struct_game(&game);
    parsing(&game, av[1]);
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE, "Cub3D");
    game.img = mlx_new_image(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE);
    game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_length, &game.endian);
    initialize_keys(&game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    if (game.map_height * TILE_SIZE > game.map_height * TILE_SIZE|| game.map_width * TILE_SIZE > game.map_width * TILE_SIZE)
    {
        printf("Map size exceed window\n");
        exit(1);
    }
    draw_map(&game);
    mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
}
