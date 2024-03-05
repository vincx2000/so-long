/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:03:13 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 16:28:08 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	srand(time(NULL));
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./so_long map_file.ber\n", 2);
		return (EXIT_FAILURE);
	}
	printf("Map Width: %d, Map Height: %d\n", game.dimensions.width1,
		game.dimensions.height1);
	get_map_dimensions(argv[1], &game);
	init_game(&game);
	setup_map(&game, argv[1]);
	start_game(&game);
	return (EXIT_SUCCESS);
}

void	init_game(t_game *game)
{
	int	window_height;
	int	window_width;

	window_width = game->dimensions.width1 * TILE_SIZE - TILE_SIZE;
	window_height = game->dimensions.height1 * TILE_SIZE + TILE_SIZE;
	printf("Map Widthfinal: %d, Map Height: %d\n", window_height, window_width);
	game->moves = 0;
	game->collectibles_collected = 0;
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, window_width, window_height,
			"so_long");
	mlx_hook(game->win_ptr, 17, 0, close_window, game);
	if (!game->mlx_ptr || !game->win_ptr)
	{
		ft_putstr_fd("Error initializing game.\n", 2);
		exit(EXIT_FAILURE);
	}
	load_sprites(game);
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
}

void	setup_map(t_game *game, char *map_file)
{
	if (!read_map_file(map_file, &game->map) || !validate_map(&game->map, game))
	{
		ft_putstr_fd("Error with map file.\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	start_game(t_game *game)
{
	render_map(game); // Render the map to the window
	mlx_loop_hook(game->mlx_ptr, (void *)update_game_state, game);
	mlx_loop(game->mlx_ptr); // Starts the MLX event loop
}
