/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:35:31 by medo              #+#    #+#             */
/*   Updated: 2025/02/04 18:30:11 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	cleanup(t_base *game, char *line)
{
	if (line)
		free(line);
	if (game->textures)
		free_texture(game->textures);
	if (game->map)
		free_split(game->map);
}

void	error_exit(t_base *game, char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = "Error\nInvalid t identifier should be as follows[NO,SO,WE,EA,F,C]\n";
	ft_printf_err(str);
	cleanup(game, line);
	free_path(game);
	exit(1);
}

void	error_color(t_base *game, char **rgb, char *str)
{
	int		i;

	i = 0;
	ft_printf_err(str);
	free_split(rgb);
	cleanup(game, NULL);
	free(game->readmap);
	free_path(game);
	exit(1);
}
