/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_n_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:36:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 22:06:30 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	handling_the_keys(int key_pressed, t_game *game)
{
	if (key_pressed == ESC_KEY)
		window_exit(game);
	else if (key_pressed == W_KEY || key_pressed == A_KEY
		|| key_pressed == S_KEY || key_pressed == D_KEY)
		player_moves(game, key_pressed);
	return (1);
}

int	window_exit(t_game *game)
{
	int	i;

	i = 0;
	if (game->fd > 0)
	{
		close(game->fd);
		game->fd = -1;
	}
	while (i < 5)
	{
		if (game->textures[i])
			mlx_destroy_image(game->mlx, game->textures[i]);
		i++;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_all(game->map_grid);
	if (game->raw_map)
		free(game->raw_map);
	exit (0);
	return (0);
}

void	player_moves(t_game *game, unsigned int key_pressed)
{
	player_lookup(game);
	if (key_pressed == D_KEY)
		player_new_position(game, game->props.player_pos_x,
			game->props.player_pos_y + 1);
	else if (key_pressed == A_KEY)
		player_new_position(game, game->props.player_pos_x,
			game->props.player_pos_y - 1);
	else if (key_pressed == W_KEY)
		player_new_position(game, game->props.player_pos_x - 1,
			game->props.player_pos_y);
	else if (key_pressed == S_KEY)
		player_new_position(game, game->props.player_pos_x + 1,
			game->props.player_pos_y);
}

void	player_lookup(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map_grid[row])
	{
		col = 0;
		while (game->map_grid[row][col])
		{
			if (game->map_grid[row][col] == 'P')
			{
				game->props.player_pos_x = row;
				game->props.player_pos_y = col;
				return ;
			}
			col++;
		}
		row++;
	}
}

void	player_new_position(t_game *game, int new_x_position,
			int new_y_position)
{
	char	target;

	if (new_x_position < 0 || new_y_position < 0
		|| new_x_position >= game->line_count
		|| new_y_position >= (int)ft_strlen(game->map_grid[0]))
		return ;
	target = game->map_grid[new_x_position][new_y_position];
	if (target == '1')
		return ;
	if (target == 'E')
	{
		if (game->props.collectible_count == 0)
		{
			game->move_count++;
			print_moves(game);
			ft_putstr("\nCongrats: You Win!");
			window_exit(game);
		}
		return ;
	}
	if (target == 'C')
		game->props.collectible_count--;
	game->map_grid[new_x_position][new_y_position] = 'P';
	game->map_grid[game->props.player_pos_x][game->props.player_pos_y] = '0';
	game->move_count++;
	game->props.player_pos_x = new_x_position;
	game->props.player_pos_y = new_y_position;
	(mlx_clear_window(game->mlx, game->win),
		create_map(game), print_moves(game));
}
