/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:15:57 by medo              #+#    #+#             */
/*   Updated: 2025/02/04 14:42:52 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

char	*trim_and_validate_line(t_base *game, char *line)
{
	size_t	len;

	len = ft_strlen2(line);
	if (line[0] == '\n' && game->map_height == 0)
		return (NULL);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

void	add_map_line(t_base *game, char *line)
{
	char	**new_map;
	int		i;

	line = trim_and_validate_line(game, line);
	if (line == NULL)
		return ;
	if (game->map == NULL)
	{
		initialize_map(game, line);
		return ;
	}
	new_map = malloc(sizeof(char *) * (game->map_height + 2));
	i = 0;
	while (i < game->map_height)
	{
		new_map[i] = game->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = NULL;
	free(game->map);
	game->map = new_map;
	game->map_height++;
	if (ft_strlen2(line) > game->map_width)
		game->map_width = ft_strlen2(line);
}

int	handle_textures_and_colors(t_base *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "D1 ", 3) == 0)
	{
		ft_parse_texture(game, line);
		return (1);
	}
	if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "C ", 2) == 0)
		&& game->check_C != 1 || game->check_F != 1)
	{
		if (!parse_color_game(game, line))
		{
			return (0);
		}
		return (1);
	}
	return (0);
}

int	check_line(t_base *game, char *line)
{
	static int	config_lines = 0;
	char		**tokens;
	char		*color_line;

	if (config_lines < 7)
	{
		if (line[0] == '\n' && line[1] == '\0')
			return (0);
		if (!handle_textures_and_colors(game, line))
		{
			error_exit(game, line);
		}
		config_lines++;
	}
	else if (game->check_NO != 1 || game->check_SO != 1 || game->check_WE != 1
		|| game->check_EA != 1 || game->check_D1 != 1 || game->check_C != 1
		|| game->check_F != 1)
	{
		error_exit(game, line);
	}
	else
		add_map_line(game, line);
	return (0);
}

int	parse_map(t_base *game, int fd)
{
	while (1)
	{
		game->readmap = get_next_line(fd);
		if (game->readmap == NULL)
			break ;
		check_line(game, game->readmap);
		free(game->readmap);
	}
	if (!game->map)
	{
		ft_printf_err("Error\nNo map found\n");
		cleanup(game, NULL);
		free_path(game);
		exit(1);
	}
	pad_map(game);
	validate_map(game);
	return (0);
}
