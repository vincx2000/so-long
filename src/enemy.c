/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:40:28 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 15:57:13 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_enemy(t_game *game) 
{
    int direction;
    int dx;
    int dy;
    int new_x;
    int new_y;

    dx = 0;
    dy = 0;
    direction = rand() % 4;
    if 
        (direction == 0) dy = 1; 
    else if 
        (direction == 1) dx = 1;  
    else if (direction == 2) 
        dy = -1; 
    else if (direction == 3) 
        dx = -1;
    new_x = game->enemy.x + dx;
    new_y = game->enemy.y + dy;
    if (is_valid_position(game, new_x, new_y)) 
    {
        game->map.array[game->enemy.y][game->enemy.x] = '0';
        game->map.array[new_y][new_x] = 'X';
        game->enemy.x = new_x;
        game->enemy.y = new_y;
    }
}

int is_valid_position(t_game *game, int x, int y)
{
    if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
        return 0;
    if (game->map.array[y][x] == '1')
        return 0;
    if (game->map.array[y][x] == 'C')
        return 0;
    if (game->map.array[y][x] == 'E')
        return 0;
    return 1;
}

void update_game_state(t_game *game) 
{
    clock_t current_time;

    current_time = clock();

    if ((current_time - game->last_enemy_move_time) > (CLOCKS_PER_SEC / 25)) 
    {
        move_enemy(game);
        game->last_enemy_move_time = current_time;
        check_collision_with_player(game);
        render_map(game);
    }
}

void check_collision_with_player(t_game *game) 
{
    if ((game->player_pos.x == game->enemy.x) && (game->player_pos.y == game->enemy.y)) 
    {
        mlx_destroy_window(game->mlx_ptr, game->win_ptr);
        exit(EXIT_SUCCESS);
    }
}

