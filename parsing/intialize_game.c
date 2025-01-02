#include "../cub.h"


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

    if (x < 0 || x >= SCREEN_SIZE || y < 0 || y >= SCREEN_HEIGHT)
        return ;
    dst = game->mlx_ptrs->addr + (y * game->mlx_ptrs->line_length + x * (game->mlx_ptrs->bpp / 8));
    *(unsigned int *)dst = color;
    
}

void draw_square(t_base *game, int x, int y, int color)
{
    int i, j;

    i = 0;
    while (i < CUB_SIZE)
    {
        j = 0;
        while (j < CUB_SIZE)
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
                draw_square(game, x, y, 0xFFFFFF);
            j++;
            x = x + CUB_SIZE; // Move to the next tile position horizontally
        }
        i++;
        y = y + CUB_SIZE; // Move to the next tile position vertically
    
    }
}
 
