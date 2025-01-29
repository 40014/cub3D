/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:15:57 by medo              #+#    #+#             */
/*   Updated: 2025/01/06 18:31:30 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

void	
parse_color_line(t_base *game, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = parse_color(game, ft_strtrim(line + 2, " "));
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = parse_color(game, ft_strtrim(line + 2, " "));
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
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "EA ",
				3) == 0 || ft_strncmp(line, "DO ",3) == 0)
			ft_parse_texture(game, line);
		else if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "C ", 2) == 0) && (game->checkc == 0 || game->checkf == 0))
		{
			if (game->checkc == 0 && ft_strncmp(line, "C ", 2) == 0)
			{
				parse_color_line(game, line);
				game->checkc = 1;
			}
			else if (game->checkf == 0 && ft_strncmp(line, "F ", 2) == 0)
			{
				parse_color_line(game, line);
				game->checkf = 1;
			}
		}
		else
			error_exit(game, line);
		config_lines++;
	}
	else if (game->checkc == 0|| game->checkf == 0)
			error_exit(game, line);
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
		exit(1);
	}
	pad_map(game);
	validate_map(game);
	return (0);
}
