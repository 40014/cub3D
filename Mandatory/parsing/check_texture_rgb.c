/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_rgb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:39:15 by momazouz          #+#    #+#             */
/*   Updated: 2025/02/04 18:28:36 by momazouz         ###   ########.fr       */
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
	i = 0;
	if (j > 2)
	{
		printf("Error\nIvalid color format, more than two commas\n");
		cleanup(game, line);
		free(game->readmap);
		free_path(game);
		exit(1);
	}
}

void	check_texture_file(t_base *game, char *file, char *tokens)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_err("Error\nTexture file doesn't exist\n");
		free_texture(game->textures);
		free(file);
		free(tokens);
		free_path(game);
		exit(1);
	}
}

void	ft_process_texture_type(t_base *game, char *texture_type, char *path)
{
	if (ft_strncmp(texture_type, "NO", 3) == 0 && game->check_NO != 1)
	{
		game->check_NO = 1;
		game->path[0] = ft_strdup(path);
	}
	else if (ft_strncmp(texture_type, "SO", 3) == 0 && game->check_SO != 1)
	{
		game->check_SO = 1;
		game->path[1] = ft_strdup(path);
	}
	else if (ft_strncmp(texture_type, "WE", 3) == 0 && game->check_WE != 1)
	{
		game->check_WE = 1;
		game->path[2] = ft_strdup(path);
	}
	else if (ft_strncmp(texture_type, "EA", 3) == 0 && game->check_EA != 1)
	{
		game->check_EA = 1;
		game->path[3] = ft_strdup(path);
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
	ft_process_texture_type(game, split[0], path);
	if (path != NULL)
		free(path);
	free_split(split);
}
