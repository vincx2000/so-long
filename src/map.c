/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:04:20 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 16:28:06 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map_file(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening map file");
		exit(EXIT_FAILURE);
	}
	map->array = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	while ((line = get_next_line(fd)) != NULL)
	{
		trim_newline(line);
		map->array[i++] = line;
	}
	map->array[i] = NULL;
	map->height = i;
	map->width = ft_strlen(map->array[0]);
	close(fd);
	free(line);
	return (map->array);
}

int	validate_map(t_map *map, t_game *game)
{
	if (!check_walls(map))
		return (0);
	game->collectibles_count = 0;
	if (!check_contents(map, game))
		return (0);
	if (game->has_exit && game->has_player && game->collectibles_count > 0)
		return (1);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(EXIT_SUCCESS);
}

void	update_dimensions(int fd, t_game *game)
{
	char	*line;

	game->dimensions.height1 = 0;
	game->dimensions.width1 = 0;
	printf("Map Width: %d, Map Height: %d\n", game->dimensions.width1,
		game->dimensions.height1);
	line = NULL;
	while ((get_next_line(fd)))
	{
		printf("Map Width11: %d, Map Height: %d\n", game->dimensions.width1,
			game->dimensions.height1);
		if (game->dimensions.height1 == 0)
			game->dimensions.width1 = strlen(get_next_line(fd));
		printf("Map Width1: %d, Map Height: %d\n", game->dimensions.width1,
			game->dimensions.height1);
		game->dimensions.height1++;
	}
	printf("Map Width: %d, Map Height: %d\n", game->dimensions.width1,
		game->dimensions.height1);
	free(line);
}

void	get_map_dimensions(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	printf("Map Width: %d, Map Height: %d\n", game->dimensions.width1,
		game->dimensions.height1);
	update_dimensions(fd, game);
	close(fd);
}
