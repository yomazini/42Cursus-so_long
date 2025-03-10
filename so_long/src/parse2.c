/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:15:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 03:44:49 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	count_map_element(t_game *game, char element_type, int x, int y)
{
	if (element_type == 'C')
		game->props.collectible_count++;
	else if (element_type == 'E')
		game->props.exit_count++;
	else if (element_type == 'P')
	{
		game->props.player_count++;
		game->props.player_pos_x = x;
		game->props.player_pos_y = y;
	}
}

int	validate_map_elements(t_game *game)
{
	game->props.collectible_count = 0;
	game->props.exit_count = 0;
	game->props.player_count = 0;
	int row, col;
	const char *valid_chars = "01PCE";

	row = 0;
	while (row < game->line_count)
	{
		col = 0;
		while (game->map_grid[row][col])
		{
			if (!ft_strchr(valid_chars, game->map_grid[row][col]))
				return (0);
			if (game->map_grid[row][col] == 'C' || 
				game->map_grid[row][col] == 'E' || 
				game->map_grid[row][col] == 'P')
				count_map_element(game, game->map_grid[row][col], row, col);
			col++;
		}
		row++;
	}
	if (game->props.collectible_count < 1 || 
		game->props.exit_count != 1 || 
		game->props.player_count != 1)
		return (0);
	return (1);
}

void	flood_fill_check(size_t x, size_t y, size_t max_lines, char **grid)
{
	// Check boundaries
	if (x < 0 || y < 0 || x >= max_lines || y >= ft_strlen(grid[0]))
		return;
	
	// Mark exit separately 
	if (grid[x][y] == 'E')
	{
		grid[x][y] = 'V'; // Mark as visited but differently
		return;
	}
	
	// Skip walls and already visited tiles
	if (grid[x][y] == '1' || grid[x][y] == 'V')
		return;
	
	// Mark current tile as visited
	grid[x][y] = 'V';
	
	// Explore in all four directions
	flood_fill_check(x - 1, y, max_lines, grid); // Up
	flood_fill_check(x + 1, y, max_lines, grid); // Down
	flood_fill_check(x, y - 1, max_lines, grid); // Left
	flood_fill_check(x, y + 1, max_lines, grid); // Right
}

int	verify_remaining_elements(char **grid)
{
	int row, col;
	
	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			// If we find collectibles or exit that weren't visited, path is invalid
			if (grid[row][col] == 'C' || grid[row][col] == 'E')
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

int	validate_map_path(t_game game)
{
	char **map_copy;
	int valid_path = 0;
	
	// Create a copy of the map for path validation
	map_copy = ft_split(game.raw_map, '\n');
	if (!map_copy)
		return (0);
	
	// Start flood fill from player position
	flood_fill_check(game.props.player_pos_x, game.props.player_pos_y, 
					game.line_count, map_copy);
	
	// Check if all collectibles and exit are reachable
	valid_path = verify_remaining_elements(map_copy);
	
	// Cleanup
	free_all(map_copy);
	
	return (valid_path);
}
