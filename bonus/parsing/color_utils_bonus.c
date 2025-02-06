/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:51:15 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/06 19:30:34 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

char	**process_line_to_rgb(t_base *game, char *line)
{
	char	*trimmed_line;
	char	**rgb;

	trimmed_line = ft_strtrim(line, " \n");
	free(line);
	check_commas(game, trimmed_line);
	rgb = ft_split(trimmed_line, ',');
	free(trimmed_line);
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
		error_color(game, rgb,
			"Error\nInvalid color : requires 3 values separated by commas.\n");
	return (rgb);
}

int	parse_color(t_base *game, char *line)
{
	char	**rgb;
	int		color;
	char	*trimmed_rgb;
	int		i;

	i = 0;
	color = -1;
	rgb = process_line_to_rgb(game, line);
	while (i < 3)
	{
		trimmed_rgb = ft_strtrim(rgb[i], " ");
		free(rgb[i]);
		rgb[i] = trimmed_rgb;
		if (!ft_isdigit_str(rgb[i]))
			error_color(game, rgb, "Error\nColor values must be numeric\n");
		i++;
	}
	color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) < 0
		|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) < 0
		|| ft_atoi(rgb[2]) > 255)
		error_color(game, rgb,
			"Error\nColor values must be between 0 and 255.\n");
	free_split(rgb);
	return (color);
}

void	parse_color_line(t_base *game, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = parse_color(game, ft_strtrim(line + 2, " "));
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = parse_color(game, ft_strtrim(line + 2, " "));
}

int	parse_color_game(t_base *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0 && game->check_f != 1)
	{
		parse_color_line(game, line);
		game->check_f = 1;
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && game->check_c != 1)
	{
		parse_color_line(game, line);
		game->check_c = 1;
		return (1);
	}
	return (0);
}
