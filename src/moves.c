/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:37:55 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 16:27:49 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESCAPE) // Example: Close window on ESC
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		exit(EXIT_SUCCESS); // Or handle cleanup differently
	}
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	return (0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_pos.x + dx;
	new_y = game->player_pos.y + dy;
	if (game->map.array[new_y][new_x] == 'E'
		&& game->collectibles_collected != game->collectibles_count)
	{
		ft_printf("You need to collect all collectibles first!\n");
		return ;
	}
	if (game->map.array[new_y][new_x] == 'X')
	{
		ft_printf("You died!\n");
		exit(EXIT_SUCCESS);
	}
	if (game->map.array[new_y][new_x] != '1')
	{
		update_moves(game);
		if (game->map.array[new_y][new_x] == 'C')
			collect_collectible(game, new_x, new_y);
		else if (game->map.array[new_y][new_x] == 'E')
			check_win_condition(game);
		update_player_position(game, new_x, new_y);
	}
	render_map(game);
}
