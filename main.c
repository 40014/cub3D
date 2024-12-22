#include "cub3D.h"

#define TILE_SIZE 32

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

int key_press(int key, t_base *game)
{
    if (key == 65307)
        exit(0);
    return (0);
}

void my_mlx_pixel_put(t_base *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= game->map_width * 32 || y < 0 || y >= game->map_height * 32)
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
    game.win = mlx_new_window(game.mlx, game.map_width * 32, game.map_height * 32, "Cub3D");
    game.img = mlx_new_image(game.mlx, game.map_width * 32, game.map_height * 32);
    game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_length, &game.endian);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    if (game.map_height * TILE_SIZE > game.map_height * 32 || game.map_width * TILE_SIZE > game.map_width * 32)
    {
        printf("Map size exceed window\n");
        exit(1);
    }
    draw_map(&game);
    mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
    mlx_loop(game.mlx);
}
