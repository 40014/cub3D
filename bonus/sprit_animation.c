/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprit_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:21:22 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/04 11:02:39 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_weapon_sprite(t_base *game, t_sprite *sprite)
{
	int				x;
	int				y;
	int				color;
	t_image_data	img_data;

	y = 0;
	img_data.current_frame_img = sprite->frames[sprite->current_frame];
	img_data.frame_data = (int *)mlx_get_data_addr(img_data.current_frame_img,
			&img_data.bpp, &img_data.line_length, &img_data.endian);
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = *(unsigned int *)(img_data.frame_data + (y
						* img_data.line_length + x * (img_data.bpp / 8)));
			if (color != 0xFF000000)
				my_mlx_pixel_put(game, sprite->x + x - sprite->width / 2,
					sprite->y + y, color);
			x++;
		}
		y++;
	}
}

void	load_sprite_frames(t_sprite *sprite, char **paths, int frame_count,
		void *mlx_ptr)
{
	int	i;

	sprite->frame_count = frame_count;
	sprite->frames = malloc(frame_count * sizeof(void *));
	if (!sprite->frames)
	{
		printf("Error: Failed to allocate memory for sprite frames\n");
		exit(1);
	}
	i = 0;
	while (i < frame_count)
	{
		sprite->frames[i] = mlx_xpm_file_to_image(mlx_ptr, paths[i],
				&sprite->width, &sprite->height);
		if (!sprite->frames[i])
		{
			printf("Error: Failed to load texture %s\n", paths[i]);
			exit(1);
		}
		i++;
	}
}

void	init_weapon_sprite(t_base *game)
{
	t_sprite	*weapon_sprite;
	static char	*weapon_sprite_paths[] = {"texture/sprit/sprite_frame1.xpm",
		"texture/sprit/sprite_frame2.xpm",
		"texture/sprit/sprite_frame3.xpm",
		"texture/sprit/sprite_frame4.xpm",
		"texture/sprit/sprite_frame5.xpm",
		"texture/sprit/sprite_frame6.xpm",
		"texture/sprit/sprite_frame7.xpm",
		"texture/sprit/sprite_frame8.xpm",
		"texture/sprit/sprite_frame9.xpm",
		"texture/sprit/sprite_frame10.xpm",
		"texture/sprit/sprite_frame11.xpm"};

	weapon_sprite = malloc(sizeof(t_sprite));
	load_sprite_frames(weapon_sprite, weapon_sprite_paths, 11,
		game->mlx_ptrs->mlx_ptr);
	weapon_sprite->x = SCREEN_SIZE / 2;
	weapon_sprite->y = SCREEN_HEIGHT - weapon_sprite->height;
	weapon_sprite->current_frame = 0;
	weapon_sprite->is_animating = 0;
	weapon_sprite->frame_timer = 0;
	game->weapon_sprite = weapon_sprite;
}
