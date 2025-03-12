/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:36:25 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/12 22:15:49 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
	put_xpm_element(game, "./textures/Flor1.xpm", 0);
	put_xpm_element(game, "./textures/walll1.xpm", 1);
	put_xpm_element(game, "./textures/Exiiit1.xpm", 2);
	put_xpm_element(game, "./textures/rameen.xpm", 3);
	put_xpm_element(game, "./textures/Naruto1.xpm", 4);
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

static	void	put_tile(t_game *game, int x, int y, char tile_type)
{
	int	img_x;
	int	img_y;

	img_x = y * TILE_SIZE;
	img_y = x * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win,
		game->textures[0], img_x, img_y);
	if (tile_type == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures[1], img_x, img_y);
	else if (tile_type == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures[2], img_x, img_y);
	else if (tile_type == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures[3], img_x, img_y);
	else if (tile_type == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures[4], img_x, img_y);
}

void	create_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map_grid[row])
	{
		col = 0;
		while (game->map_grid[row][col])
		{
			put_tile(game, row, col, game->map_grid[row][col]);
			col++;
		}
		row++;
	}
}
