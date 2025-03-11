/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 22:20:12 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	cleanup_resources(t_game *game)
{
	if (game->raw_map)
	{
		free(game->raw_map);
		game->raw_map = NULL;
	}
	if (game->map_grid)
	{
		free_all(game->map_grid);
		game->map_grid = NULL;
	}
	if (game->fd > 0)
	{
		close(game->fd);
		game->fd = 0;
	}
}

void	free_all(char **grid)
{
	int	row;

	row = 0;
	if (!grid)
		return ;
	while (grid[row])
	{
		free(grid[row]);
		row++;
	}
	free(grid);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	if (len == 0)
		return (b);
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	print_moves(t_game *game)
{
	char	*nmr_moves;

	nmr_moves = ft_itoa(game->move_count);
	ft_putstr(">Player moves: ");
	ft_putstr(nmr_moves);
	ft_putstr("\n");
	free(nmr_moves);
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
