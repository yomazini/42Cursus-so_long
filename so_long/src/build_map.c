/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:36:25 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 21:44:10 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	build_graphic_map(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	get_dimention_map(game);
	if (game->window_width > 5120 || game->window_height > 2880)
	{
		perror("\nError: Map dimensions too large");
		free(game->mlx);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "So_Long");
	if (!game->win)
	{
		free(game->mlx);
		return (0);
	}
	imgs_to_map(game);
	create_map(game);
	mlx_hook(game->win, 2, 0, handling_the_keys, game);
	mlx_hook(game->win, ON_DESTROY, 0, window_exit, game);
	mlx_loop(game->mlx);
	return (1);
}

void	get_dimention_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (game->map_grid[row])
	{
		col = ft_strlen(game->map_grid[row]);
		row++;
	}
	game->window_width = col * TILE_SIZE;
	game->window_height = row * TILE_SIZE;
	game->img_width = game->window_width;
	game->img_height = game->window_height;
}

void	imgs_to_map(t_game *game)
{
	put_xpm_element(game, "./textures/route.xpm", 0);
	put_xpm_element(game, "./textures/wall.xpm", 1);
	put_xpm_element(game, "./textures/exit.xpm", 2);
	put_xpm_element(game, "./textures/nud.xpm", 3);
	put_xpm_element(game, "./textures/player.xpm", 4);
}

void	put_xpm_element(t_game *game, char *name_of_xpm, int order)
{
	game->textures[order] = mlx_xpm_file_to_image(game->mlx, name_of_xpm,
			&game->props.width, &game->props.height);
	if (!game->textures[order])
	{
		perror("Error In Texture: ");
		free_all(game->map_grid);
		free(game->mlx);
		free(game->win);
		exit(1);
	}
}

void	create_map(t_game *game)
{
	int	row;
	int	col;
	int	x;
	int	y;

	row = 0;
	while (game->map_grid[row])
	{
		col = 0;
		while (game->map_grid[row][col])
		{
			x = col * TILE_SIZE;
			y = row * TILE_SIZE;
			mlx_put_image_to_window(game->mlx, game->win,
				game->textures[0], x, y);
			if (game->map_grid[row][col] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->textures[1], x, y);
			else if (game->map_grid[row][col] == 'E')
				mlx_put_image_to_window(game->mlx, game->win,
					game->textures[2], x, y);
			else if (game->map_grid[row][col] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->textures[3], x, y);
			else if (game->map_grid[row][col] == 'P')
				mlx_put_image_to_window(game->mlx, game->win,
					game->textures[4], x, y);
			col++;
		}
		row++;
	}
}
