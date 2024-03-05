/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:37:17 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/05 14:57:14 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#define BUFFER_SIZE 1024
#define TILE_SIZE 32

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESCAPE 53
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124


# include "../others/printf/ft_printf.h"
# include "../others/get_next_line/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>  
# include "../others/minilibx/mlx.h"
# include <string.h>
# include <time.h>

typedef struct s_dimensions
{
    int     width1;
    int     height1;
} t_dimensions;

typedef struct s_enemy 
{
    int     x;
    int     y;
} t_enemy;

typedef struct s_map
{
    char    **array; 
    int     width;  
    int     height;  
} t_map;

typedef struct s_player
{
    int     x;
    int     y;
} t_player;

// Define your game structure
typedef struct s_game
{
    void            *mlx_ptr;
    void            *win_ptr;
    t_map           map;
    void            *wall;
    void            *player;
    void            *collectibles;
    int             collectibles_count;
    void            *exit;
    t_player        player_pos;
    int             collectibles_collected;
    int             moves;
    int             has_player;
    int             has_exit;
    void            *floor;
    clock_t         last_enemy_move_time;
    void            *enemy_sprite;
    t_enemy         enemy;
    t_dimensions    dimensions;
    
} t_game;


// Function declarations
char    **read_map_file(char *filename, t_map *map);
int     validate_map(t_map *map, t_game *game);
void    ft_putstr_fd(char *s, int fd);
void    trim_newline(char *line); 
void    setup_map(t_game *game, char *map_file);
void    init_game(t_game *game);
void    start_game(t_game *game);
void    load_sprites(t_game *game);
void    render_map(t_game *game);
void    *choose_sprite(t_game *game, char tile);
int     handle_keypress(int keycode, t_game *game);
void    move_player(t_game *game, int dx, int dy);
void    update_moves(t_game *game);
void    collect_collectible(t_game *game, int new_x, int new_y);
void    check_win_condition(t_game *game);
void    update_player_position(t_game *game, int new_x, int new_y);
int     check_walls(t_map *map);
int     check_contents(t_map *map, t_game *game);
int     is_valid_position(t_game *game, int x, int y);
void    move_enemy(t_game *game);
void    update_game_state(t_game *game);
void    check_collision_with_player(t_game *game);
void    draw_tiles(t_game *game, int x, int y);
int     close_window(t_game *game);
void    update_dimensions(int fd, t_game *dimensions);
void    get_map_dimensions(char *filename, t_game *game);


#endif