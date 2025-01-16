/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_rgb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:31:46 by medo              #+#    #+#             */
/*   Updated: 2025/01/06 13:34:42 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_commas(t_base *game, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j > 2)
	{
		printf("Error\nIvalid color format, more than two commas\n");
		cleanup(game, line);
		free(game->readmap);
		exit(19);
	}
}

void	check_texture_file(t_base *game, char *file, char *tokens)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_err("Error\nTexture file doesn't exist\n");
		free_texture(game->textures);
		free(file);
		free(tokens);
		exit(111);
	}
}

void	ft_parse_texture(t_base *game, char *tokens)
{
	int		index;
	char	*path;
	char	**split;

	path = NULL;
	path = ft_strtrim(tokens + 3, " \t\n");
	check_texture_file(game, path, tokens);
	split = ft_split(tokens, ' ');
	if (ft_strncmp(split[0], "NO", 3) == 0)
		index = 0;
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		index = 1;
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		index = 2;
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		index = 3;
	game->path[index] = ft_strdup(path);
	if (path != NULL)
		free(path);
	free_split(split);
}

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
