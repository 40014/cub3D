#include "cub.h"

void draw_sprite_frame(t_base *game, t_sprite *sprite)
{
    int         x;
    int         y;
    void        *current_frame_img;
    char        *frame_data;
    int         bpp;
    int         line_length;
    int         endian;
    int         color;
    char        *pixel_addr;

    y = 0;
    current_frame_img = sprite->frames[sprite->current_frame];
    frame_data = mlx_get_data_addr(current_frame_img, &bpp, &line_length, &endian);
    while (y < sprite->height)
    {
        x = 0;
        while (x < sprite->width)
        {
            color = *(unsigned int *)(frame_data + (y * line_length + x * (bpp / 8)));
            if (color != 0x000000)
                my_mlx_pixel_put(game, sprite->x + x - sprite->width / 2, sprite->y + y, color);
            x++;
        }
        y++;
    }
}

void draw_weapon_sprite(t_base *game)
{
    draw_sprite_frame(game, game->weapon_sprite);
}
void load_sprite_frames(t_sprite *sprite, char **paths, int frame_count, void *mlx_ptr)
{
    int     i;

    i = 0;
    sprite->frame_count = frame_count;
    sprite->frames = malloc(frame_count * sizeof(void *)); // Allocate memory for frame pointers
    if (!sprite->frames)
        return ;
    while  (i < frame_count)
    {
        sprite->frames[i] = mlx_xpm_file_to_image(mlx_ptr, paths[i], &sprite->width, &sprite->height);
        if (!sprite->frames[i])
            return ;
        i++;
    }
}

void init_weapon_sprite(t_base *game)
{
     t_sprite   *weapon_sprite;
    static char *weapon_sprite_paths[] = {
        "texture/sprit/sprite_frame1.xpm",
        "texture/sprit/sprite_frame2.xpm",
        "texture/sprit/sprite_frame3.xpm",
        "texture/sprit/sprite_frame4.xpm",
    };

    weapon_sprite = malloc(sizeof(t_sprite));
    load_sprite_frames(weapon_sprite, weapon_sprite_paths, 4, game->mlx_ptrs->mlx_ptr);
    weapon_sprite->x = SCREEN_SIZE / 2;
    weapon_sprite->y = SCREEN_HEIGHT - weapon_sprite->height;
    game->weapon_sprite = weapon_sprite;
    game->weapon_sprite->current_frame = 0;
    
}