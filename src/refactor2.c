/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:39:56 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 16:28:27 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_contents(t_map *map, t_game *game)
{
	int		i;
	int		j;
	char	tile;

	i = 0;
	game->has_exit = 0;
	game->has_player = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			tile = map->array[i][j];
			if (tile == 'E')
				game->has_exit = 1;
			else if (tile == 'C')
				game->collectibles_count++;
			else if (tile == 'P')
				game->has_player = 1;
			j++;
		}
		i++;
	}
	return (game->has_exit && game->has_player);
}

int	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->array[0][i] != '1' || map->array[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->array[i][0] != '1' || map->array[i][map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
