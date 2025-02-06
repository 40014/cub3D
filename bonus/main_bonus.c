/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:15:49 by hdrahm            #+#    #+#             */
/*   Updated: 2025/02/06 13:15:50 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	main(int ac, char **av)
{
	t_base	game;

	if (ac != 2)
		return (1);
	ft_init_struct_game(&game);
	parsing(&game, av[1]);
	initialize_game(&game);
	return (0);
}
