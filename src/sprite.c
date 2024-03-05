/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:35:10 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 16:28:04 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*choose_sprite(t_game *game, char tile)
{
	if (tile == '1')
		return (game->wall);
	else if (tile == 'P')
		return (game->player);
	else if (tile == 'C')
		return (game->collectibles);
	else if (tile == 'E')
		return (game->exit);
	else if (tile == '0')
		return (game->floor);
	else if (tile == 'X')
		return (game->enemy_sprite);
	return (NULL);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			draw_tiles(game, x, y);
			x++;
		}
		y++;
	}
}

void	draw_tiles(t_game *game, int x, int y)
{
	char	tile;
	void	*sprite;

	tile = game->map.array[y][x];
	sprite = choose_sprite(game, tile);
	if (tile == 'P')
	{
		game->player_pos.x = x;
		game->player_pos.y = y;
	}
	else if (tile == 'X')
	{
		game->enemy.x = x;
		game->enemy.y = y;
	}
	if (sprite)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite, x
			* TILE_SIZE, y * TILE_SIZE);
}

void	load_sprites(t_game *game)
{
	int img_width, img_height;

	game->wall = mlx_xpm_file_to_image(game->mlx_ptr, "include/wall.xpm",
			&img_width, &img_height);
	game->player = mlx_xpm_file_to_image(game->mlx_ptr, "include/player.xpm",
			&img_width, &img_height);
	game->collectibles = mlx_xpm_file_to_image(game->mlx_ptr,
			"include/collectibles.xpm", &img_width, &img_height);
	game->exit = mlx_xpm_file_to_image(game->mlx_ptr, "include/exit.xpm",
			&img_width, &img_height);
	game->floor = mlx_xpm_file_to_image(game->mlx_ptr, "include/floor.xpm",
			&img_width, &img_height);
	game->enemy_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"include/enemy.xpm", &img_width, &img_height);
	// Check if sprites are loaded successfully
	if (!game->wall || !game->player || !game->collectibles || !game->exit)
	{
		ft_putstr_fd("Error loading sprites.\n", 2);
		exit(EXIT_FAILURE);
	}
}