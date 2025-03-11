/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 18:00:11 by ymazini          ###   ########.fr       */
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
    if (game->map_grid) {
        free_all(game->map_grid);
        game->map_grid = NULL;
    }
	close(game->fd);
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
void *ft_memset(void *b, int c, size_t len)
{
    unsigned char *ptr;
    
    ptr = (unsigned char*)b;
    while (len--)
        *ptr++ = (unsigned char)c;
    return (b);
}
