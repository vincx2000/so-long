/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:02:05 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 16:27:57 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_moves(t_game *game)
{
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	collect_collectible(t_game *game, int new_x, int new_y)
{
	game->collectibles_collected += 1;
	ft_printf("Collectibles collected: %d\n", game->collectibles_collected);
	game->map.array[new_y][new_x] = '0';
}

void	check_win_condition(t_game *game)
{
	if (game->collectibles_count == game->collectibles_collected)
	{
		ft_printf("You win!\n");
		exit(EXIT_SUCCESS);
	}
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map.array[game->player_pos.y][game->player_pos.x] = '0';
	game->map.array[new_y][new_x] = 'P';
	game->player_pos.x = new_x;
	game->player_pos.y = new_y;
}
