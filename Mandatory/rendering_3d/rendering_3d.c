/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:39:53 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/06 19:17:01 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_ceiling(t_base *game, double x, double start_wall)
{
	double	i;

	i = 0;
	while (i < start_wall)
	{
		my_mlx_pixel_put(game, x, i, game->ceiling_color);
		i++;
	}
}

void	draw_wall(t_base *game, double x, t_wall_data *wall_data)
{
	double		y;
	int			tex_y;
	double		texture_step;
	double		texture_pos;
	t_texture	*texture;

	texture = game->textures[wall_data->n];
	y = wall_data->start_wall;
	texture_step = (double)texture->height / wall_data->line_length;
	texture_pos = (wall_data->start_wall - ((SCREEN_HEIGHT / 2)
				- (wall_data->line_length / 2))) * texture_step;
	while (y < wall_data->end_wall)
	{
		tex_y = (int)texture_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		wall_data->color = *(unsigned int *)((char *)texture->data + (tex_y
					* texture->line_length + wall_data->tex_x * (texture->bpp
						/ 8)));
		my_mlx_pixel_put(game, x, y, wall_data->color);
		texture_pos += texture_step;
		y++;
	}
}

void	draw_floor(t_base *game, double x, double end_wall)
{
	double	i;

	i = end_wall;
	while (i < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, i, game->floor_color);
		i++;
	}
}

void	draw_wall_line(t_base *game, double line_length, double x, int n)
{
	t_wall_data	wall_data;

	wall_data.start_wall = (SCREEN_HEIGHT / 2) - (line_length / 2);
	wall_data.end_wall = wall_data.start_wall + line_length;
	wall_data.line_length = line_length;
	wall_data.tex_x = game->tex_x;
	wall_data.n = n;
	if (wall_data.start_wall < 0)
		wall_data.start_wall = 0;
	if (wall_data.end_wall > SCREEN_HEIGHT)
		wall_data.end_wall = SCREEN_HEIGHT;
	draw_ceiling(game, x, wall_data.start_wall);
	draw_wall(game, x, &wall_data);
	draw_floor(game, x, wall_data.end_wall);
}

void	rendering_3d(t_base *game)
{
	double	start_angle;
	double	increment;
	double	distance_projection;
	double	wall_height;
	int		colome;

	start_angle = game->player_infos->rotation_angle - (FOV / 2) * (M_PI / 180);
	game->player_infos->ray_rotation_angle = start_angle;
	distance_projection = (SCREEN_SIZE / 2) / (tan((FOV / 2) * (M_PI / 180)));
	increment = FOV * (M_PI / 180) / SCREEN_SIZE;
	colome = 0;
	while (colome < SCREEN_SIZE)
	{
		wall_height = get_wall_height(game->player_infos, distance_projection);
		game->wall_x = calculate_wall_x(game->player_infos);
		game->n = get_texture_index(game->player_infos, game->n);
		game->tex_x = get_texture_x(game, game->wall_x, game->n);
		draw_wall_line(game, wall_height, colome, game->n);
		game->player_infos->ray_rotation_angle += increment;
		colome++;
	}
}
