/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:15:17 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/10 03:41:38 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	validate_map_file(char *path, t_game *game)
{
	game->fd = open(path, O_RDONLY);
	if (game->fd == -1)
	{
		perror("\nError opening map file");
		return (0);
	}
	game->raw_map = NULL;
	game->line_count = 0;
	if (!process_map_content(game))
		return (0);
	return (1);
}

int	process_map_content(t_game *game)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break;
		temp = game->raw_map;
		game->raw_map = ft_strjoin(game->raw_map, line);
		free(temp);
		if (!game->raw_map || line[0] == '\n')
		{
			free(line);
			free(game->raw_map);
			close(game->fd);
			return (0);
		}
		free(line);
		game->line_count++;
	}
	game->map_grid = ft_split(game->raw_map, '\n');
	if (!game->map_grid || !verify_map_shape(game) || !validate_map_elements(game) 
		|| !validate_map_path(*game))
	{
		cleanup_resources(game);
		return (0);
	}
	return (1);
}

int	verify_map_shape(t_game *game)
{
	int		i;
	int		last_line;
	size_t	len;

	i = 0;
	last_line = game->line_count - 1;
	while (i <= last_line)
	{
		if ((i != last_line) && 
			ft_strlen(game->map_grid[i]) != ft_strlen(game->map_grid[i + 1]))
			return (0);
		if ((i == 0 || i == last_line) && !check_wall_border(game, i))
			return (0);
		if (game->map_grid[i][0] != '1' || 
			game->map_grid[i][ft_strlen(game->map_grid[i]) - 1] != '1')
			return (0);
		i++;
	}
	len = ft_strlen(game->raw_map);
	if (game->raw_map[len - 1] == '\n')
		return (0);
	return (1);
}

int	check_wall_border(t_game *game, int line_idx)
{
	int	col;

	col = 0;
	while (game->map_grid[line_idx][col])
	{
		if (game->map_grid[line_idx][col] != '1')
			return (0);
		col++;
	}
	return (1);
}
